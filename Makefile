
###########################################################
# Build Instructions					  #
# ------------------					  #
# 							  #
# If you want to build this yourself, you'll need	  #
# CMake version 3.15 or later and a			  #
# C++ compiler supporting C++20 or later.		  #
# 							  #
# 1. Download or clone the source:  			  #
#    `git clone https://github.com/j4james/vtinterco.git` #
# 							  #
# 2. Change into the build directory:  			  #
#    `cd vtinterco/build`				  #
# 							  #
# 3. Generate the build project:  			  #
#    `cmake -D CMAKE_BUILD_TYPE=Release ..`		  #
# 							  #
# 4. Start the build:  					  #
#    `cmake --build . --config Release`			  #
###########################################################

all:	debug

release:
	cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
	cmake --build build --config Release

debug:
	cmake -S . -B build -D CMAKE_BUILD_TYPE=Debug
	cmake --build build --config Debug

clean:
	cmake --build build --target clean
