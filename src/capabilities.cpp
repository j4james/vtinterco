// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#include "capabilities.h"

#include "os.h"
#include "vt.h"

#include <cstring>

using namespace std::string_literals;

capabilities::capabilities()
{
    // Save the cursor position.
    vtout.decsc();
    // Request 7-bit C1 controls from the terminal.
    vtout.s7c1t();
    // Determine the screen size.
    vtout.cup(999, 999);
    vtout.dsr(6);
    const auto size = _query(R"(\x1B\[(\d+);(\d+)R)", false);
    if (!size.empty()) {
        height = std::stoi(size[1]);
        width = std::stoi(size[2]);
    }
    // Retrieve the device attributes report.
    _query_device_attributes();
    // Disable Sixel display mode.
    _original_decsdm = query_mode(80);
    vtout.rm('?', 80);
    has_sixel_display_mode = _original_decsdm.has_value();
    // Restore the cursor position.
    vtout.decrc();
}

capabilities::~capabilities()
{
    // Restore the original DECSDM mode.
    if (_original_decsdm == true)
        vtout.sm('?', 80);
    else if (_original_decsdm == false)
        vtout.rm('?', 80);
    vtout.flush();
}

std::optional<bool> capabilities::query_mode(const int mode) const
{
    vtout.decrqm('?', mode);
    const auto report = _query(R"(\x1B\[\?(\d+);(\d+)\$y)", true);
    if (!report.empty()) {
        const auto returned_mode = std::stoi(report[1]);
        const auto status = std::stoi(report[2]);
        if (returned_mode == mode) {
            if (status == 1) return true;
            if (status == 2) return false;
        }
    }
    return {};
}

std::string capabilities::query_setting(const std::string_view setting) const
{
    vtout.decrqss(setting);
    const auto report = _query(R"(\x1BP1\$r(.*)\x1B\\)", true);
    if (!report.empty())
        return report[1];
    else
        return {};
}

std::string capabilities::query_color_table() const
{
    vtout.decctr(2);
    const auto report = _query(R"(\x1BP2\$s(.*)\x1B\\)", true);
    if (!report.empty())
        return report[1];
    else
        return {};
}

void capabilities::_query_device_attributes()
{
    vtout.da();
    // The Reflection Desktop terminal sometimes uses comma separators
    // instead of semicolons in their DA report, so we allow for either.
    const auto report = _query(R"(\x1B\[\?(\d+)([;,\d]*)c)", false);
    if (!report.empty()) {
        // The first parameter indicates the terminal conformance level.
        const auto level = std::stoi(report[1]);
        // As long as it's 61+ we know we're using the new DA encoding scheme.
        if (level >= 61) {
            // The remaining parameters indicate additional feature extensions.
            const auto features = report[2].str();
            const auto digits = std::regex(R"(\d+)");
            auto it = std::sregex_iterator(features.begin(), features.end(), digits);
            while (it != std::sregex_iterator()) {
                const auto feature = std::stoi(it->str());
                switch (feature) {
                    case 4: has_sixels = true; break;
                    case 7: has_soft_fonts = true; break;
                }
                it++;
            }
        }
    }
}

std::smatch capabilities::_query(const char* pattern, const bool may_not_work)
{
    auto final_char = pattern[strlen(pattern) - 1];
    if (may_not_work) {
        // If we're uncertain this query is supported, we'll send an extra
        // DSR-CPR query to make sure that we get some kind of response.
        final_char = 'R';
        vtout.dsr(6);
    }
    vtout.flush();
    // This needs to be static so the returned smatch can reference it.
    static auto response = std::string{};
    response.clear();
    auto last_escape = 0;
    for (;;) {
        const auto ch = os::getch();
        // Ignore XON, XOFF
        if (ch == '\021' || ch == '\023')
            continue;
        // If we've sent an extra query, the last escape should be the
        // start of that response, which we'll ultimately drop.
        if (may_not_work && ch == '\033')
            last_escape = response.length();
        response += ch;
        if (ch == final_char) break;
    }
    // Drop the extra response if one was requested.
    if (may_not_work)
        response = response.substr(0, last_escape);
    auto match = std::smatch{};
    std::regex_match(response, match, std::regex(pattern));
    return match;
}
