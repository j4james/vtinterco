// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#include "debug.h"

#include "vt.h"

#include <filesystem>
#include <format>
#include <fstream>
#include <string>

namespace {

    static constexpr auto header = R"(#!/bin/bash

ESC=$'\e'	# Escape
CSI=$'\e['	# Control Sequence Introducer 
DCS=$'\eP'	# Device Control String
ST=$'\e\\'	# String Terminator
BS=$'\b'	# Backspace
LS0=$'\017'	# Locking Shift 0
LS1=$'\016'	# Locking Shift 1

echo -n ${CSI}'?25l'  # Hide cursor

)";

    auto capture_log = std::string{header};

}  // namespace

void debug::clear()
{
    vtout.flush();
    capture_log.clear();
    capture_log.append(header);
}

void debug::record(const std::string_view s)
{
    auto in_quotes = false;
    auto line_buffer = std::string{};

    auto echo = [&](auto newline) {
        if (!line_buffer.empty() || newline) {
            capture_log += "echo ";
            if (!newline)
                capture_log += "-n ";
            if (line_buffer.empty())
                capture_log += "''";
            else {
                capture_log += line_buffer;
                if (in_quotes) capture_log += "'";
            }
            capture_log += "\n";
            line_buffer.clear();
            in_quotes = false;
        }
    };

    auto quote = [&](auto s) {
        if (!in_quotes) {
            line_buffer += "'";
            in_quotes = true;
        }
        line_buffer += s;
    };

    auto unquote = [&](auto s) {
        if (in_quotes) {
            line_buffer += "'";
            in_quotes = false;
        }
        line_buffer += s;
    };

    for (auto i = 0; i < s.length(); i++) {
        auto ch = s[i];
        if (ch == '\n')
            echo(true);
        else if (ch == '\b')
            unquote("${BS}");
        else if (ch == '\017')
            unquote("${LS0}");
        else if (ch == '\016')
            unquote("${LS1}");
        else if (ch == '\'')
            unquote("\\'");
        else if (ch == '\033') {
            if (i + 1 >= s.length()) {
                echo(false);
                unquote("${ESC}");
            } else {
                switch (s[++i]) {
                    case '[':
                        echo(false);
                        unquote("${CSI}");
                        break;
                    case 'P':
                        echo(false);
                        unquote("${DCS}");
                        break;
                    case '\\':
                        unquote("${ST}");
                        break;
                    default:
                        echo(false);
                        unquote("${ESC}");
                        i--;
                        break;
                }
            }
        } else {
            quote(ch);
        }
    }
    echo(false);
}

int debug::getch(std::function<int()>&& key_supplier)
{
    vtout.flush();
    capture_log.append("\nread -s -n 1  # Wait for keypress\n\n");

    for (;;) {
        auto ch = key_supplier();
        if (ch != 18) return ch;

        const auto capture_time = std::time(nullptr) - 1740182400;
        const auto capture_name = std::format("cap-{}.sh", capture_time);
        const auto capture_path = std::filesystem::current_path().append(capture_name);
        auto capture_file = std::ofstream{capture_path, std::ios::binary};
        capture_file << capture_log;
        capture_file << "echo -n ${CSI}'?25h'  # Restore cursor\n";
    }
}
