VT INTERCO
==========

![Screenshot](screenshot.png)

This is a terminal application to help you learn the nautical signal flags from
the [International Code of Signals]. It requires a VT340 terminal to run (or at
least a Sixel terminal emulator of comparable functionality).

DISCLAIMER: For entertainent purposes only. Do not rely the accuracy of this
application for any critical flag signaling needs.

[International Code of Signals]: https://en-wp.org/wiki/International_Code_of_Signals


Download
--------

The latest binaries can be found on GitHub at the following url:

https://github.com/j4james/vtinterco/releases/latest

For Linux download `vtinterco`, and for Windows download `vtinterco.exe`.


Build Instructions
------------------

If you want to build this yourself, you'll need [CMake] version 3.15 or later
and a C++ compiler supporting C++20 or later.

1. Download or clone the source:  
   `git clone https://github.com/j4james/vtinterco.git`

2. Change into the build directory:  
   `cd vtinterco/build`

3. Generate the build project:  
   `cmake -D CMAKE_BUILD_TYPE=Release ..`

4. Start the build:  
   `cmake --build . --config Release`

[CMake]: https://cmake.org/


Supported Terminals
-------------------

* DEC VT340
* Windows Terminal (> v1.22.2702.0)


License
-------

The VT INTERCO source code and binaries are released under the MIT License.
See the [LICENSE] file for full license details.

[LICENSE]: LICENSE.txt
