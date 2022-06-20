cmake_minimum_required(VERSION 3.20)
project(IniLib2)

set(CMAKE_CXX_STANDARD 17)


set(SOURCE_FILES code/src/IniSection.cpp code/include/IniSection.hpp code/src/IniParser.cpp code/include/IniParser.hpp code/include/Exceptions.hpp)

add_executable(IniLib2 main.cpp ${SOURCE_FILES})
