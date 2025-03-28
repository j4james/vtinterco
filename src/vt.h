// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#pragma once

#include <array>
#include <initializer_list>
#include <iostream>
#include <string_view>

using vt_parm = int;
using vt_parms = std::initializer_list<vt_parm>;

class vt_stream {
public:
    vt_stream(std::ostream& stream);
    ~vt_stream();
    void ls0();
    void ls1();
    void cup(const vt_parm row = {}, const vt_parm col = {});
    void cuu(const vt_parm rows = {});
    void cud(const vt_parm rows = {});
    void ed(const vt_parm type = {});
    void el(const vt_parm type = {});
    void sgr(const vt_parms attrs = {});
    void sm(const char prefix, const vt_parm mode);
    void rm(const char prefix, const vt_parm mode);
    void sm(const char prefix, const vt_parms modes);
    void rm(const char prefix, const vt_parms modes);
    void dsr(const vt_parm id);
    void scs(const int gset, const std::string_view id);
    void da();
    void s7c1t();
    void ind();
    void decsc();
    void decrc();
    void decdhlt();
    void decdhlb();
    void decdwl();
    void decrqm(const char prefix, const vt_parm mode);
    std::string_view vt_response(const std::string_view final);
    std::string_view read_decrqss(const std::string_view setting);
    void decrqss(const std::string_view setting);
    void decac(const vt_parm a, const vt_parm b, const vt_parm c);
    void decctr(const std::string_view colors);
    void decctr(const vt_parm type);
    void decswt(const std::string_view s = {});
    void decssdt(const vt_parm Ps);
    void decsasd(const vt_parm Ps);
    void sixel(const std::string_view s);
    void dcs(const std::string_view s);
    void write(const std::string_view s);
    void write_double_width(const std::string_view s);
    void write_double_height(const std::string_view s);
    void flush();
    void set_status(std::string s);
    char *receive_media_copy();
    void setup_media_copy();
    void mediacopy_to_host();
    void save_region_to_file(char *filename, int x1, int y1, int x2, int y2);

private:
    void _csi();
    void _final(const std::string_view chars);
    void _parm(const vt_parm value);
    void _parms(const vt_parms parms, const bool compact = true);
    void _number(const int n);
    void _string(const std::string_view s);
    void _char(const char ch);

    std::ostream& _stream;
    std::array<char, 8192> _buffer = {};
    int _buffer_index = 0;
};

extern vt_stream vtout;
