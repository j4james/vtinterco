// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#include "vt.h"

#include "capabilities.h"
#include "debug.h"

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

std::string_view vt_stream::vt_response(const std::string_view final)
{
    // Read a string from the terminal until the string "final" is seen.
    // The entire string is returned.

    // XXX This ought to timeout. Termios works for Linux. What about Windows?
    //     termios cc[VTIME] = 10;  termios cc[VMIN] = 0;

    int c;
    std::string buffer = {};

    vtout.flush();
    while (!buffer.ends_with(final)) {
	if ( (c = getchar()) != EOF )
	    buffer += c;
	else
	    break;		// Timeout, error, or EOF
    }
    return buffer;
}

void vt_stream::decrqss(const std::string_view final)
{
    // Sends the DECRQSS sequence for final, does not return results
    // Result printed to stdin is in the DECRPSS format: DCS Ps $ r D...D ST
    //        Where Ps is 1 if the request is valid, 0 otherwise;
    //          and D...D is the current setting + the final.
    _string("\033P$q");
    _string(final);
    _string("\033\\");
}

std::string_view vt_stream::read_decrqss(const std::string_view final)
{
    // Request the status of a VT setting whose esc seq ends in `final`.
    // Returned string is the current setting + the final.
    _string("\033P$q");
    _string(final);
    _string("\033\\");

    std::string r = std::string(vt_response("\033\\"));

    // If valid response, return just the data D...D + the 'final'.
    if (r.starts_with("\033P1$r") && r.ends_with("\033\\") ) {
	r = r.substr(6, r.length()-2);
    }
    else {
	r = {};
    }
    return r;
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

void vt_stream::decsasd(const vt_parm Ps)
{
    // Select Active Status Display
    // 0: Send data to main display; 1: to status line only.
    _csi();
    _parm(Ps);
    _final("$}");
}

void vt_stream::decssdt(const vt_parm Ps)
{
    // Select Status Line Type
    // 0: None; 1: Indicator; 2: Host-writable
    _csi();
    _parm(Ps);
    _final("$~");
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

void vt_stream::mediacopy_to_host()
{
    setup_media_copy();
    save_screen_to_file("screenshot.six");
}

void vt_stream::setup_media_copy()
{
    _csi();
    _char('?');
    _parm(2);   // MC: Media Copy, "2" means send graphics to host, not printer
    _final("i");
    
    // DECGEPM: Graphics Expanded Print Mode (not used by Level 2 Graphics)
    sm('?', 43);		// Set: 1600x480, Reset: 800x240
    // DECGPCM: Print Graphics Color Mode
    sm('?', 44);		// Set: Color, Reset: B&W
    // DECGPCS: Print Graphics Color Syntax
    sm('?', 45);		// Set: RGB, Reset: HLS
    // DECGPBM: Print Graphics Background Mode
    sm('?', 46);		// Set: Include background, Reset: Omit bg
    // DECGRPM: Print Graphics Rotated Print Mode (also sets ANSI grid size)
    rm('?', 47);		// Set: Landscape, Reset: Portrait (shrunk)
}
    

char *vt_stream::receive_media_copy() 
{
  // Read stdin and return DCS data received on stdin as a malloc'd string.

  // Nota Bene:
  // * DCS (Esc P) at the start and ST's \ at the end will be missing. 
  // * The result must be freed by the calling routine.
  /* * The terminal must be in cbreak or raw mode */

  // Since media copy is not delimited, we look for the DCS string
  // (Esc P) that starts the sixel data. The VT340 in Level 2 sixel
  // mode, actually always sends a string terminator, a carriage
  // return, and sets the DPI before the sixel data, so we have to
  // skip over those. (Esc \ CR Esc [ 2 SP I). 

  // Side note: Expecting Esc P not a bug
  //
  // * This code does not handle 8-bit DCS (0x90) and ST (0x9C). The
  //   VT340 documentation states that Media Copy will never generate
  //   sixels using those characters, even in 8-bit mode. This has
  //   been confirmed on hackerb9's vt340).

  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  
  int delim='\e';		/* Chop up input on Esc */

  /* Read data from terminal until next Esc character. */
  char c = '\0';
  while (c != 'P') {
    /* Skip everything until we get to a Device Control String (Esc P) */
    nread = getdelim(&line, &len, delim, stdin); 
    if (nread == -1) {perror("receive_media_copy, getdelim"); _exit(1);}
    c = getchar(); // Character after the Esc ("P" for DCS string)
  }

  /* We got Esc P, now read the rest of the string up to the first Esc */
  nread = getdelim(&line, &len, delim, stdin); 
  if (nread == -1) {perror("receive_media_copy, getdelim"); _exit(1);}
  c = getchar(); // Character after the Esc ("\" for String Terminator)

  return line;
}

void vt_stream::set_status(std::string s)
{
    decsasd(1);
    _string(s);
    decsasd(0);
}

void vt_stream::save_screen_to_file(const char *filename)
{
    save_region_to_file(filename, 0, 0, 0, 0);
}

void vt_stream::save_region_to_file(const char *filename, int x1, int y1, int x2, int y2) {

  FILE *fp = fopen(filename, "w");
  if (!fp) { perror(filename);  _exit(1); } /* Flush stdout of REGIS MC */

  char *regis_h;		/* regis select rectangle to print */

  if ( x2 <= x1 || y2 <= y1 ) {
      asprintf(&regis_h, "p S(H)");
  } else {
      /* x1,y1 - x2,y2: Area to copy, 0,0 is upper left corner */
      asprintf(&regis_h, "p S(H(P[0,0])[%d,%d][%d,%d])", x1, y1, x2, y2);
  }
  
  // Save setting for status line
  capabilities cap;
  std::string_view old_ssdt = cap.query_setting("$~");
  if (!old_ssdt.empty()) { 
      decssdt(2);		// Show our own status line
      std::string statusline =
	  std::string(regis_h) +
	  std::string("Saving screenshot to file '") +
	  std::string(filename) + "'";
      set_status(statusline);
  }

  // Send sixel "hard copy" to host using REGIS
  dcs(regis_h);
  vtout.flush();
  char *buf = receive_media_copy();
  fprintf(fp, "\eP%s\\", buf);
  
  if (!old_ssdt.empty()) {
      set_status({});
      _csi();
      _string(old_ssdt);
  }

  if (buf) { free(buf); buf=NULL; }
  if (regis_h) { free(regis_h); regis_h=NULL; }
  fclose(fp);
}


void vt_stream::flush()
{
    if (_buffer_index) {
        if (this == &vtout)
            debug::record({&_buffer[0], (size_t) _buffer_index});
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
