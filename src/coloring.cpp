// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#include "coloring.h"

#include "capabilities.h"
#include "vt.h"

coloring::coloring(const capabilities& caps)
{
    _color_table = caps.query_color_table();
    _color_assignment = caps.query_setting("1,|");
    // On terminals that manage the text palette indendently of the graphics
    // palette, we'll need to set the 7 and 0 text entries with DECCTR, because
    // we want a black on sky-blue color scheme. We should also make sure the
    // the default color indices are set to 7 and 0, and apply reverse screen
    // mode to get color index 7 (the sky blue) as the background.
    vtout.decctr("0;2;0;0;0/7;2;57;78;95");
    vtout.decac(1, 7, 0);
    vtout.sm('?', 5);
    // In the Sixel graphics palette, indices 1, 2, 5, 6, and 8 are used for
    // the flags colors (blue, red, white, yellow, and black), indices 3 and 4
    // are used by for right/wrong check marks (green and red), and index 7 is
    // the sky blue background color, same as the text palette set above.
    vtout.sixel("#1;2;0;0;58#2;2;100;0;0#3;2;0;58;0#4;2;58;0;0#5;2;100;100;100#6;2;100;80;0#7;2;57;78;95#8;2;0;0;0");
}

coloring::~coloring()
{
    // Reset reverse screen mode, and restore the original color table and text
    // color assignments (assuming we were able to save them on startup).
    vtout.rm('?', 5);
    if (!_color_table.empty())
        vtout.decctr(_color_table);
    if (!_color_assignment.empty())
        vtout.write("\033[" + _color_assignment);
}
