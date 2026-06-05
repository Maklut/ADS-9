set(header_path "${CMAKE_CURRENT_SOURCE_DIR}/../include")
set(header ${header_path}/tree.h)
set(src alg.cpp)

add_library(${PROJECT_NAME} SHARED
    ${src})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_executable(${PROJECT_NAME}.info main.cpp)
target_include_directories(${PROJECT_NAME}.info
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(${PROJECT_NAME}.info
    ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
install(TARGETS ${PROJECT_NAME}.info
    RUNTIME DESTINATION bin)
install(FILES ${header} DESTINATION include)
