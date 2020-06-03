set(MY_ENUM_TESTS EnumTest EnumOStreamTest EnumFlagsTest EnumFlagsOStreamTest)

foreach(TEST ${MY_ENUM_TESTS})
    add_executable(${TEST} ${TEST}.cpp ${MY_ENUM_HEADER_FILES})
    add_test(NAME ${TEST} COMMAND ${TEST})
    target_link_libraries(${TEST} PRIVATE fmt::fmt MyEnum)
    target_include_directories(${TEST} PRIVATE ${Boost_INCLUDE_DIRS})
endforeach()
