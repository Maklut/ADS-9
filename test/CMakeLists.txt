enable_testing()
find_package(GTest REQUIRED)

add_executable(tests tests.cpp)
target_include_directories(tests
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(tests
    PermutationTree
    GTest::gtest_main)

add_test(NAME PermutationTreeTests COMMAND tests)
