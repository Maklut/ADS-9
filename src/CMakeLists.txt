cmake_minimum_required(VERSION 3.10)
project(PermutationTree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(lib_dest lib)
set(tool_dest bin)
set(include_dest include)

set(header_path "${${PROJECT_NAME}_SOURCE_DIR}/include")
set(header ${header_path}/tree.h)
set(src alg.cpp)

add_library(${PROJECT_NAME} SHARED
  ${header}
  ${src})
  
target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
         ${${PROJECT_NAME}_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}
  pthread)

add_executable(${PROJECT_NAME}.info main.cpp)
target_include_directories(${PROJECT_NAME}.info
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
         ${${PROJECT_NAME}_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}.info
  ${PROJECT_NAME})

# Для тестов
enable_testing()
find_package(GTest REQUIRED)
add_executable(tests test.cpp)
target_include_directories(tests
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
         ${${PROJECT_NAME}_SOURCE_DIR}/include)
target_link_libraries(tests
  ${PROJECT_NAME}
  GTest::GTest
  GTest::Main)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION "${lib_dest}"
    ARCHIVE DESTINATION "${lib_dest}"
    COMPONENT library)
install(TARGETS ${PROJECT_NAME}.info
        RUNTIME DESTINATION "${tool_dest}"
    COMPONENT library)
install(FILES ${header} DESTINATION "${include_dest}")
