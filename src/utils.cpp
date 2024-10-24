// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#include "utils.h"

#include "vt.h"

#include <sstream>

namespace utils {

    std::tuple<std::string, int> wrap_text(const std::string_view s, const size_t width, const bool dwl, const bool clear)
    {
        auto line_count = 1;
        auto buffer = std::ostringstream{};
        auto vt = vt_stream{buffer};
        for (auto source = s;;) {
            auto pos = source.rfind(' ', width);
            if (source.length() <= width || pos == std::string::npos) {
                vt.write(source);
                break;
            }
            vt.decsc();
            vt.write(source.substr(0, pos));
            if (clear) vt.el();
            vt.decrc();
            vt.ind();
            if (dwl) vt.decdwl();
            source = source.substr(pos + 1);
            line_count++;
        }
        if (clear) vt.el();
        vt.flush();
        return {buffer.str(), line_count};
    }

    void transform_fractions(std::string& s)
    {
        const auto replace = [&](const std::string_view unicode, const std::string_view scs) {
            auto pos = s.find(unicode);
            if (pos != std::string::npos)
                s.replace(pos, unicode.length(), scs);
        };
        // We're converting the Unicode fractions into two-character
        // representations that are rendered with a custom font in G1.
        replace("½", "\016'2\017");
        replace("⅓", "\016'3\017");
        replace("¼", "\016'4\017");
        replace("⅔", "\016+3\017");
        replace("⅝", "\016*8\017");
    }

}  // namespace utils
