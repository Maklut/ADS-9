enable_testing()
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}.test tests.cpp)
target_include_directories(${PROJECT_NAME}.test
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(${PROJECT_NAME}.test
    ${PROJECT_NAME}
    GTest::gtest_main)

add_test(NAME PermutationTreeTests COMMAND ${PROJECT_NAME}.test)
