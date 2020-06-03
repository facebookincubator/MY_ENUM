cmake_minimum_required(VERSION 3.10)

project(MY_ENUM VERSION 1.0
                DESCRIPTION "Small c++ macro library to add compile-time introspection to c++ enum classes."
                LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 14)
add_library(MyEnum INTERFACE)

# needed for boost preprocessor only
find_package(Boost 1.62 REQUIRED)

# needed for fmt::string_view and logging using fmt::format.
find_package(fmt 5.2 REQUIRED)

set(MY_ENUM_HEADER_FILES
    ../Enum.h
    ../EnumO.h
    ../impl/EnumDetails.h
    ../EnumFlags.h
    ../EnumFlagsO.h
    ../impl/EnumFlagsDetails.h
    ../impl/CompilerAttributes.h)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

option(BUILD_EXAMPLES "Build examples." ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
