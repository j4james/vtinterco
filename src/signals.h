// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#pragma once

#include <span>
#include <string>
#include <string_view>

struct signal {
    std::string_view flags;
    std::string_view description;

    static std::span<const signal> code_words();
    static std::span<const signal> figure_words();
    static std::span<const signal> single_flags();
    static std::span<const signal> double_flags();

    static std::string_view code_word(const char c);
    static std::string code_words(const std::string_view letters);
    static std::string morse(const std::string_view letters);
    static std::string describe(const std::string_view letters);
};
