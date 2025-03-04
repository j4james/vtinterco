// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#include "viewer.h"

#include "capabilities.h"
#include "flags.h"
#include "os.h"
#include "signals.h"
#include "utils.h"
#include "vt.h"

namespace viewer {

    void view_alphabet_flags(const capabilities& caps)
    {
        vtout.cup();
        vtout.ed();

        const auto half_width = caps.width / 2;
        const auto width = half_width * 2;

        const auto title_row = (caps.height - 22) / 2 + 1;
        const auto title_column = (half_width - 14) / 2 + 1;

        const auto flags_row = title_row + 3;
        const auto flags_column = (width - 66) / 2 + 1;

        vtout.cup(title_row, title_column);
        vtout.write_double_height("Alphabet Flags");

        for (auto i = 0; i < 26; i++) {
            const auto letter = 'A' + i;
            const auto row = flags_row + (i / 7) * 5;
            const auto col = flags_column + (i % 7 + (i > 20)) * 10;
            vtout.cup(row, col);
            vtout.sixel(flags::small(letter));
            vtout.cup(row + 3, col);
            vtout.write(signal::code_word(letter));
        }

        vtout.flush();
        os::getch();
    }


    void view_numeral_pennants(const capabilities& caps)
    {
        vtout.cup();
        vtout.ed();

        const auto half_width = caps.width / 2;
        const auto width = half_width * 2;

        const auto title_row = (caps.height - 16) / 2 + 1;
        const auto title_column = (half_width - 16) / 2 + 1;

        const auto flags_row = title_row + 4;
        const auto flags_column = (width - 66) / 2 + 1;

        vtout.cup(title_row, title_column);
        vtout.write_double_height("Numeral Pennants");

        for (auto i = 0; i < 10; i++) {
            const auto n = (i + 1) % 10;
            const auto letter = '0' + n;
            const auto row = flags_row + (i / 5) * 6;
            const auto col = flags_column + (i % 5) * 14;
            vtout.cup(row, col);
            vtout.sixel(flags::small(letter));
            vtout.cup(row + 3, col);
            vtout.write(signal::code_word(letter));
        }

        vtout.flush();
        os::getch();
    }

    void lookup_letter_sequence(const capabilities& caps)
    {
        vtout.cup();
        vtout.ed();

        const auto half_width = caps.width / 2;
        const auto origin_row = (caps.height - 20) / 2 + 1;
        const auto origin_column = (half_width - 25) / 2 + 1;
        const auto narrow_origin_column = origin_column * 2 - 1;
        const auto prompt_row = origin_row + 20;
        const auto prompt_column = origin_column + 11;

        vtout.scs(0, "0");
        vtout.cup(prompt_row, origin_column);
        vtout.write_double_width("qqqqqqqqqu     tqqqqqqqqq");
        vtout.scs(0, "B");
        vtout.sgr({7});
        vtout.cup(prompt_row, prompt_column - 1);
        vtout.write("     ");
        vtout.sgr();

        vtout.cup(origin_row);
        vtout.decdhlt();
        vtout.ind();
        vtout.decdhlb();
        vtout.ind();
        vtout.decdwl();

        auto letters = std::to_array({' ', ' ', ' '});
        auto count = size_t{};

        const auto show_instructions = [&]() {
            vtout.cup(prompt_row - 2, origin_column + 3);
            vtout.write_double_width("Enter flag sequence");
        };
        const auto clear_instructions = [&]() {
            vtout.cup(prompt_row - 2);
            vtout.el();
        };
        show_instructions();

        for (;;) {
            const auto last_count = count;

            vtout.flush();
            auto ch = std::toupper(os::getch());
            if (ch == 27) {
                break;
            } else if (ch == 127) {
                if (count <= 0) break;
                count--;
                letters[count] = ' ';
            } else if ((ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9' && count != letters.size())) {
                count = count % letters.size();
                if (!count) letters[1] = letters[2] = ' ';
                letters[count] = ch;
                count++;
                if (signal::describe({&letters[0], count}).empty()) {
                    count--;
                    letters[count] = ' ';
                }
            }

            if (count != last_count) {
                auto name = signal::code_words({&letters[0], count});
                auto morse = signal::morse({&letters[0], count});
                auto description = signal::describe({&letters[0], count});
                auto description_height = 0;
                std::tie(description, description_height) = utils::wrap_text(description, 50, false, true);
                utils::transform_fractions(description);

                if (count == 0)
                    show_instructions();
                else if (last_count == 0)
                    clear_instructions();

                const auto render_flag = [&](auto i) {
                    const auto row_off = letters[i] >= 'A' ? 10 : 11;
                    vtout.cup(origin_row + row_off, narrow_origin_column + i * 14);
                    const auto sixel = std::string{flags::medium(letters[i])};
                    vtout.sixel(sixel);
                };
                const auto erase_flag = [&](auto i) {
                    vtout.cup(origin_row + 10, narrow_origin_column + i * 14);
                    vtout.sixel(i == 0 ? R"("20;1#7!120~)" : R"("20;1#7!200~)");
                };
                const auto render_description = [&]() {
                    vtout.sgr();
                    vtout.cup(origin_row, origin_column);
                    vtout.write_double_height(name + "\033[K");
                    vtout.cup(origin_row + 2, origin_column);
                    vtout.ls1();
                    vtout.write_double_width(morse);
                    vtout.ls0();
                    vtout.el();
                    vtout.cup(origin_row + 4, narrow_origin_column);
                    vtout.write(description);
                    for (auto i = description_height; i < 6; i++) {
                        vtout.cup(origin_row + 4 + i, narrow_origin_column);
                        vtout.el();
                    }
                };

                vtout.sgr({7});
                if (count > last_count) {
                    vtout.cup(prompt_row, prompt_column + last_count);
                    vtout.write_double_width({&letters[last_count], 1});
                    render_description();
                    render_flag(last_count);
                } else if (ch == 127) {
                    vtout.cup(prompt_row, prompt_column + count);
                    vtout.write_double_width(" ");
                    render_description();
                    erase_flag(count);
                } else {
                    vtout.cup(prompt_row, prompt_column);
                    vtout.write_double_width({&letters[0], letters.size()});
                    render_description();
                    erase_flag(0);
                    erase_flag(1);
                    erase_flag(2);
                    render_flag(0);
                }
            }
        }
    }

}  // namespace viewer
