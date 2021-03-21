cmake_minimum_required(VERSION 3.5)
project(library_loader)

set(CMAKE_CXX_STANDARD 14)

file(GLOB src_list ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_library(library_loader SHARED ${src_list})
target_include_directories(library_loader PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/../common)
target_link_directories(library_loader PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../build)
target_link_libraries(library_loader PUBLIC common)

add_library(library_animal_1 SHARED ${CMAKE_CURRENT_LIST_DIR}/test_lib/library_animal_1.cpp)
target_include_directories(library_animal_1 PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/test_lib)
target_link_libraries(library_animal_1 PUBLIC library_loader)

add_library(library_animal_2 SHARED ${CMAKE_CURRENT_LIST_DIR}/test_lib/library_animal_2.cpp)
target_include_directories(library_animal_2 PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/test_lib)
target_link_libraries(library_animal_2 PUBLIC library_loader)