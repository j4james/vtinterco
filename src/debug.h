// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#pragma once

#include <functional>
#include <string_view>

class debug {
public:
    static void clear();
    static void record(const std::string_view s);
    static int getch(std::function<int()>&& key_supplier);
};
