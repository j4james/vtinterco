// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#include "quizzes.h"

#include "capabilities.h"
#include "debug.h"
#include "flags.h"
#include "os.h"
#include "utils.h"
#include "vt.h"

#include <chrono>
#include <format>
#include <numeric>
#include <random>
#include <thread>

using namespace std::chrono_literals;
using namespace std::string_literals;

namespace {

    auto random_generator = std::mt19937{std::random_device{}()};

    template <typename T>
    std::optional<int> find_index(const std::vector<T> haystack, const T needle)
    {
        const auto it = std::find(haystack.begin(), haystack.end(), needle);
        if (it == haystack.end()) return {};
        return static_cast<int>(it - haystack.begin());
    }

    std::string underline_first_char(const std::string_view s)
    {
        return std::format("\033[4m{}\033[m{}", s[0], s.substr(1));
    }

    std::string prefix_with_number(const int number, const std::string_view s)
    {
        return std::format("{}. {}", number, s);
    }

}  // namespace


quiz::quiz(const std::string_view title, const std::span<const signal> signals, const type quiz_type)
    : _title{title}, _signals{signals}, _quiz_type{quiz_type}
{
    _boxes[0].resize(_signals.size());
    std::iota(_boxes[0].begin(), _boxes[0].end(), 0);
}

void quiz::run(const capabilities& caps)
{
    const auto half_width = caps.width / 2;
    const auto origin_row = (caps.height - 15) / 2 + 1;
    const auto origin_column = (half_width - 36) / 2 + 1;
    const auto narrow_origin_column = (origin_column - 1) * 2 + 1;

    const auto single_flag = _signals[0].flags.length() == 1;
    const auto title_row = single_flag ? origin_row : (origin_row + 1);
    const auto title_column = origin_column + (single_flag ? 19 : 12);
    const auto title_width = single_flag ? 17 : 22;
    const auto text_width = title_width * 2 - 3;

    const auto question_count = 10;
    auto correct_count = 0;
    for (auto i = 0; i < question_count; i++) {
        debug::clear();
        vtout.cup();
        vtout.ed();

        vtout.cup(title_row, title_column);
        vtout.write_double_width(std::get<0>(utils::wrap_text(_title, title_width, true)));

        const auto question_index = _next_question();
        const auto answers = _possible_answers(question_index);
        const auto expected_index = find_index(answers, question_index);

        auto tick_column = 0;
        auto answer_rows = std::vector<int>(answers.size());
        for (auto index = 0, answer_row = title_row + 3; index < answers.size(); index++) {
            const auto text = _signals[answers[index]].description;
            if (_quiz_type == type::letters) {
                vtout.cup(answer_row, title_column + 4);
                vtout.write_double_height(underline_first_char(text));
                answer_rows[index] = answer_row;
                answer_row += 3;
                tick_column = title_column * 2 + 1;
            } else if (_quiz_type == type::figures) {
                vtout.cup(answer_row, title_column + 3);
                vtout.write_double_height(text);
                answer_rows[index] = answer_row;
                answer_row += 3;
                tick_column = title_column * 2 - 1;
            } else {
                auto [wrapped_text, line_count] = utils::wrap_text(text, text_width);
                utils::transform_fractions(wrapped_text);
                vtout.cup(answer_row, title_column * 2 - 1);
                vtout.write(prefix_with_number(index + 1, wrapped_text));
                answer_rows[index] = answer_row;
                answer_row += line_count + 1;
                tick_column = title_column * 2 - 6;
            }
        }

        // When you output a Sixel image on the VT340, it resets the internal
        // line attributes of the page, so the position of the image should be
        // relative to the single-width cursor offset, even if you started on
        // a double-width line. But this reset isn't immediate, which can result
        // in the image being partially rendered in the wrong position. To avoid
        // that, we output a blank image in advance, which forces the reset to
        // occur before we output the actual flag image.
        vtout.sixel("");

        const auto flags = _signals[question_index].flags;
        if (single_flag) {
            const auto flag_row = _quiz_type == type::figures ? origin_row + 4 : origin_row;
            vtout.cup(flag_row, narrow_origin_column);
            vtout.sixel(flags::large(flags[0]));
        } else {
            for (auto flag_index = 0; flag_index < flags.size(); flag_index++) {
                vtout.cup(origin_row + flag_index * 7 + 1, narrow_origin_column + 4);
                vtout.sixel(flags::medium(flags[flag_index]));
            }
        }
        vtout.flush();

        const auto answer_index = _read_answer(answers);
        if (!answer_index) {
            _answer_is_wrong();
            return;
        }

        if (answer_index == expected_index) {
            correct_count++;
            _answer_is_correct();
            _display_tick(answer_rows[answer_index.value()] - 1, tick_column, true);
            vtout.flush();
            std::this_thread::sleep_for(0.5s);
        } else {
            _answer_is_wrong();
            _display_tick(answer_rows[answer_index.value()] - 1, tick_column, false);
            _display_tick(answer_rows[expected_index.value()] - 1, tick_column, true);
            vtout.flush();
            const auto ch = os::getch();
            if (ch == 27 || ch == 127) return;
        }
    }

    debug::clear();
    vtout.cup();
    vtout.ed();

    const auto score = std::format("{} out of {}", correct_count, question_count);
    const auto percent = correct_count * 100 / question_count;
    const auto message = percent == 100 ? "Perfect!"s : (percent >= 70 ? "Well done!"s : (percent >= 50 ? "Not bad"s : "Needs improvement"s));
    vtout.cup(origin_row + 5, (half_width - message.length()) / 2 + 1);
    vtout.write_double_height(message);
    vtout.cup(origin_row + 8, (half_width - score.length()) / 2 + 1);
    vtout.write_double_height(score);
    vtout.flush();

    os::getch();
}

int quiz::_next_question()
{
    _box_entry++;
    while (_box_entry >= _current.size()) {
        _iteration++;
        if (_iteration % 5 == 0)
            _box = 2;
        else if (_iteration % 3 == 0)
            _box = 1;
        else
            _box = 0;
        if (_boxes[_box].size()) {
            _current.swap(_boxes[_box]);
            _boxes[_box].clear();
            _box_entry = 0;
            _shuffle();
        }
    }
    return _current[_box_entry];
}

std::vector<int> quiz::_possible_answers(const int question_index) const
{
    static constexpr auto required_answers = 4;
    const auto step = _signals.size() / required_answers;
    auto answers = std::vector<int>(required_answers);
    for (auto i = 0, value = question_index; i < required_answers; i++) {
        answers[i] = value;
        value = (value + step) % _signals.size();
    }
    std::shuffle(answers.begin(), answers.end(), random_generator);
    return answers;
}

std::optional<int> quiz::_read_answer(const std::vector<int> answers) const
{
    auto index = std::optional<int>{};
    while (!index) {
        const auto ch = os::getch();
        if (ch == 27 || ch == 127)
            break;
        switch (_quiz_type) {
            case type::letters:
                if (ch >= 'a' && ch <= 'z')
                    index = find_index(answers, ch - 'a');
                else if (ch >= 'A' && ch <= 'Z')
                    index = find_index(answers, ch - 'A');
                break;
            case type::figures:
                if (ch >= '0' && ch <= '9')
                    index = find_index(answers, ch - '0');
                break;
            default:
                if (ch >= '1' && ch < '1' + answers.size())
                    index = ch - '1';
                break;
        }
    }
    return index;
}

void quiz::_display_tick(const int row, const int column, const bool correct) const
{
    static constexpr auto tick_glyph = "#3----!34?!4_-!28?_ow{}!4~^^F-!8?o!6wo_!6?_ow}!5~^NFB@-!9?@BF^!5~}{w{}!5~^FB@-!14?@FN!6~^^FB-!19?@@";
    static constexpr auto cross_glyph = "#4----!28?__!7o-!9?ow!4{wwoo_?_oww{}!5~^NNFB@-!10?@BBFNn!10~NFB@-!10?_w{}!5~^NN^!4~}{w_-!9?^!4~^NF@!5?@BF^!4~^-!10?@@@!14?@@@";
    auto glyph = std::string{correct ? tick_glyph : cross_glyph};
    if (_quiz_type == type::general) glyph[3] = glyph[4] = ' ';
    vtout.cup(row, column);
    vtout.sixel(glyph);
}

void quiz::_answer_is_wrong()
{
    _boxes[0].push_back(_current[_box_entry]);
}

void quiz::_answer_is_correct()
{
    const auto next_box = std::min(_box + 1, 2);
    _boxes[next_box].push_back(_current[_box_entry]);
}

void quiz::_shuffle()
{
    std::shuffle(_current.begin(), _current.end(), random_generator);
}

quiz quiz::code_words("What letter does this represent?", signal::code_words(), quiz::type::letters);
quiz quiz::figure_words("What number does this represent?", signal::figure_words(), quiz::type::figures);
quiz quiz::single_flags("What does this flag mean?", signal::single_flags(), quiz::type::general);
quiz quiz::double_flags("What does this flag combination mean?", signal::double_flags(), quiz::type::general);
