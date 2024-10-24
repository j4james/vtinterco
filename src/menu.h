// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#pragma once

#include <initializer_list>
#include <optional>
#include <string_view>
#include <vector>

class capabilities;

class menu {
public:
    menu(const capabilities& caps, const std::initializer_list<std::string_view> options);
    std::optional<int> get_choice() const;

private:
    const capabilities& _caps;
    const std::vector<std::string_view> _options;
    mutable int _choice = 0;
};
