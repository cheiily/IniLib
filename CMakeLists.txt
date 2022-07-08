cmake_minimum_required(VERSION 3.20)
project(IniLib)

set(Boost_DEBUG true)
set(Boost_VERBOSE true)
set(Boost_ROOT D:\\Boost\\install)
set(Boost_ARCHITECTURE -x86)
include_directories(${BOOST_INCLUDE_DIRS})
find_package(Boost 1.79.0 REQUIRED COMPONENTS unit_test_framework)


set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        code/src/IniSection.cpp code/include/IniSection.hpp
        code/src/IniParser.cpp code/include/IniParser.hpp
        code/include/Exceptions.hpp)
set(TEST_FILES
        tests/master.cpp
        tests/scenarios/SectionTests.cpp tests/scenarios/ParserCore/ParserCoreTest.cpp tests/scenarios/ParserCore/ParserNestingTests.cpp tests/scenarios/ParserCore/ParserConfigHandlingTests.cpp)

add_executable(IniLib main.cpp ${SOURCE_FILES})
add_executable(IniLib_Check tests/master.cpp ${SOURCE_FILES} ${TEST_FILES})

target_link_libraries(IniLib_Check Boost::unit_test_framework)

enable_testing()