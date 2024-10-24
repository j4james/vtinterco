// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#pragma once

#include <string>

class capabilities;

class coloring {
public:
    coloring(const capabilities& caps);
    ~coloring();

private:
    std::string _color_assignment;
    std::string _color_table;
};
