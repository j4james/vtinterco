// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#pragma once

#include "signals.h"

#include <array>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

class capabilities;

class quiz {
public:
    static quiz code_words;
    static quiz figure_words;
    static quiz single_flags;
    static quiz double_flags;

    enum class type {
        letters,
        figures,
        general
    };

    quiz(const std::string_view title, const std::span<const signal> signals, const type quiz_type);
    void run(const capabilities& caps);

private:
    int _next_question();
    std::vector<int> _possible_answers(const int question_index) const;
    std::optional<int> _read_answer(const std::vector<int> answers) const;
    void _display_tick(const int row, const int column, const bool correct) const;
    void _answer_is_wrong();
    void _answer_is_correct();
    void _shuffle();

    std::string _title;
    std::span<const signal> _signals;
    type _quiz_type;
    int _iteration = 0;
    int _box = 0;
    int _box_entry = -1;
    std::array<std::vector<int>, 3> _boxes;
    std::vector<int> _current;
};
