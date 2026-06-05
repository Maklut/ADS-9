find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}.test tests.cpp AllTests.cpp)
target_include_directories(${PROJECT_NAME}.test
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(${PROJECT_NAME}.test
    ${PROJECT_NAME}
    GTest::gtest_main)

add_test(NAME ${PROJECT_NAME}Tests COMMAND ${PROJECT_NAME}.test)
