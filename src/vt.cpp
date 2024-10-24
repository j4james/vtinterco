// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#include "vt.h"

#include <chrono>
#include <thread>

vt_stream vtout{std::cout};

vt_stream::vt_stream(std::ostream& stream)
    : _stream{stream}
{
}

vt_stream::~vt_stream()
{
    flush();
}

void vt_stream::ls0()
{
    _char('\017');
}

void vt_stream::ls1()
{
    _char('\016');
}

void vt_stream::cup(const vt_parm row, const vt_parm col)
{
    _csi();
    _parms({row, col});
    _final("H");
}

void vt_stream::cuu(const vt_parm rows)
{
    _csi();
    _parm(rows);
    _final("A");
}

void vt_stream::cud(const vt_parm rows)
{
    _csi();
    _parm(rows);
    _final("B");
}

void vt_stream::ed(const vt_parm type)
{
    _csi();
    _parm(type);
    _final("J");
}

void vt_stream::el(const vt_parm type)
{
    _csi();
    _parm(type);
    _final("K");
}

void vt_stream::sgr(const vt_parms attrs)
{
    _csi();
    _parms(attrs);
    _final("m");
}

void vt_stream::sm(const char prefix, const vt_parm mode)
{
    sm(prefix, {mode});
}

void vt_stream::rm(const char prefix, const vt_parm mode)
{
    rm(prefix, {mode});
}

void vt_stream::sm(const char prefix, const vt_parms modes)
{
    _csi();
    _char(prefix);
    _parms(modes);
    _final("h");
}

void vt_stream::rm(const char prefix, const vt_parms modes)
{
    _csi();
    _char(prefix);
    _parms(modes);
    _final("l");
}

void vt_stream::dsr(const vt_parm id)
{
    _csi();
    _parm(id);
    _final("n");
}

void vt_stream::scs(const int gset, const std::string_view id)
{
    _char('\033');
    _char("()*+"[gset]);
    _string(id);
}

void vt_stream::da()
{
    _string("\033[c");
}

void vt_stream::s7c1t()
{
    _string("\033 F");
}

void vt_stream::ind()
{
    _string("\033D");
}

void vt_stream::decsc()
{
    _string("\0337");
}

void vt_stream::decrc()
{
    _string("\0338");
}

void vt_stream::decdhlt()
{
    _string("\033#3");
}

void vt_stream::decdhlb()
{
    _string("\033#4");
}

void vt_stream::decdwl()
{
    _string("\033#6");
}

void vt_stream::decrqm(const char prefix, const vt_parm mode)
{
    _csi();
    _char(prefix);
    _parm(mode);
    _final("$p");
}

void vt_stream::decrqss(const std::string_view setting)
{
    _string("\033P$q");
    _string(setting);
    _string("\033\\");
}

void vt_stream::decac(const vt_parm a, const vt_parm b, const vt_parm c)
{
    _csi();
    _parms({a, b, c});
    _final(",|");
}

void vt_stream::decctr(const std::string_view colors)
{
    _string("\033P2$p");
    _string(colors);
    _string("\033\\");
}

void vt_stream::decctr(const vt_parm type)
{
    _csi();
    _parms({2, type});
    _final("$u");
}

void vt_stream::decswt(const std::string_view s)
{
    _string("\033]21;");
    write(s);
    _string("\033\\");
}

void vt_stream::sixel(const std::string_view s)
{
    _string("\033P9;1q");
    _string(s);
    _string("\033\\");
}

void vt_stream::dcs(const std::string_view s)
{
    _string("\033P");
    _string(s);
    _string("\033\\");
}

void vt_stream::write(const std::string_view s)
{
    _string(s);
}

void vt_stream::write_double_width(const std::string_view s)
{
    decdwl();
    _string(s);
}

void vt_stream::write_double_height(const std::string_view s)
{
    decsc();
    decdhlt();
    _string(s);
    decrc();
    ind();
    decdhlb();
    _string(s);
}

void vt_stream::flush()
{
    if (_buffer_index) {
        _stream.write(&_buffer[0], _buffer_index);
        _stream.flush();
        _buffer_index = 0;
    }
}

void vt_stream::_csi()
{
    _string("\033[");
}

void vt_stream::_final(const std::string_view chars)
{
    _string(chars);
}

void vt_stream::_parm(const vt_parm value)
{
    if (value) _number(value);
}

void vt_stream::_parms(const vt_parms parms, const bool compact)
{
    auto last_good = -1;
    auto i = 0;
    for (const auto parm : parms) {
        if (parm) last_good = i;
        i++;
    }
    i = 0;
    for (const auto parm : parms) {
        if (i > last_good && compact) break;
        if (i > 0) _char(';');
        if (parm) _number(parm);
        i++;
    }
}

void vt_stream::_number(const int n)
{
    if (n >= 10) _number(n / 10);
    _char('0' + (n % 10));
}

void vt_stream::_string(const std::string_view s)
{
    for (auto ch : s)
        _char(ch);
}

void vt_stream::_char(const char ch)
{
    _buffer[_buffer_index++] = ch;
    if (_buffer_index == _buffer.size())
        flush();
}
