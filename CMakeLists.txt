cmake_minimum_required(VERSION 3.15)
project(vtinterco)

set(
    MAIN_FILES
    "src/main.cpp"
    "src/capabilities.cpp"
    "src/coloring.cpp"
    "src/debug.cpp"
    "src/flags.cpp"
    "src/font.cpp"
    "src/menu.cpp"
    "src/os.cpp"
    "src/quizzes.cpp"
    "src/signals.cpp"
    "src/utils.cpp"
    "src/viewer.cpp"
    "src/vt.cpp"
)

set(
    DOC_FILES
    "README.md"
    "LICENSE.txt"
)

if(WIN32)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

add_executable(vtinterco ${MAIN_FILES})

set_target_properties(vtinterco PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED On)
source_group("Doc Files" FILES ${DOC_FILES})
