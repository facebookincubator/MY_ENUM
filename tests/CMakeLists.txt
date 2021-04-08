set(MY_ENUM_TESTS EnumTest EnumOStreamTest EnumFlagsTest EnumFlagsOStreamTest)

add_subdirectory(googletest)

foreach(TEST ${MY_ENUM_TESTS})
    add_executable(${TEST} ${TEST}.cpp ${MY_ENUM_HEADER_FILES})
    add_test(NAME ${TEST} COMMAND ${TEST})
    target_link_libraries(${TEST} PRIVATE ${STRING_VIEW_LIB} MyEnum gtest gmock gtest_main pthread)
    target_include_directories(${TEST} PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endforeach()
