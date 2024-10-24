// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#pragma once

#include <string>
#include <string_view>
#include <tuple>

namespace utils {

    std::tuple<std::string, int> wrap_text(const std::string_view s, const size_t width, const bool dwl = false, const bool clear = false);
    void transform_fractions(std::string& s);

}  // namespace utils
