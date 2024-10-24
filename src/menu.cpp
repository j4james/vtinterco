// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#include "menu.h"

#include "capabilities.h"
#include "os.h"
#include "vt.h"

#include <algorithm>

menu::menu(const capabilities& caps, const std::initializer_list<std::string_view> options)
    : _caps{caps}, _options{options}
{
}

std::optional<int> menu::get_choice() const
{
    vtout.cup();
    vtout.ed();

    const auto half_width = _caps.width / 2;
    const auto width = half_width * 2;

    const auto menu_height = _options.size() + 4;
    const auto menu_width = std::max_element(_options.begin(), _options.end(), [](auto s1, auto s2) {
        return s1.size() < s2.size();
    })->size();

    const auto title_column = (half_width - 15) / 2 + 1;
    const auto title_row = (_caps.height - menu_height) / 2 + 1;

    vtout.cup(title_row, title_column + 1);
    vtout.write_double_width("INTERNATIONAL");
    vtout.cup(title_row + 1, title_column);
    vtout.write_double_height("CODE OF SIGNALS");

    const auto menu_column = (width - menu_width) / 2 + 1;
    const auto menu_row = title_row + 4;
    for (auto i = 0; i < _options.size(); i++) {
        vtout.cup(menu_row + i, menu_column);
        vtout.write(_options[i]);
    }

    vtout.cup(menu_row + _choice, menu_column - 2);
    vtout.write(">\b");
    vtout.flush();

    for (;;) {
        const auto old_choice = _choice;

        // In lieu of a full escape sequence parser, we're just checking for the
        // final characters of the up arrow and down arrow key reports.
        switch (os::getch()) {
            case 'A':
                _choice--;
                break;
            case 'B':
                _choice++;
                break;
            case '\r':
            case '\n':
                if (_choice < _options.size() - 1)
                    return _choice;
                else
                    return std::nullopt;
        }

        if (_choice != old_choice) {
            _choice = (_choice + _options.size()) % _options.size();
            vtout.write(" \b");
            if (old_choice < _choice)
                vtout.cud(_choice - old_choice);
            else
                vtout.cuu(old_choice - _choice);
            vtout.write(">\b");
            vtout.flush();
        }
    }
}
