cmake_minimum_required(VERSION 3.10)
project(misc)

set(CMAKE_CXX_STANDARD 14)

file(GLOB modules ${CMAKE_CURRENT_LIST_DIR}/*)

find_package(Threads REQUIRED)
set(system_libs
    Threads::Threads
    dl)

enable_testing()

foreach(module_dir ${modules})
    if(${module_dir} MATCHES ".*wip")
        continue()
    endif()
    if(IS_DIRECTORY ${module_dir})
        get_filename_component(module ${module_dir} NAME)
        file(GLOB src_list ${module}/*.cpp)
        if(src_list)
            message(STATUS "build module ${module}")
            add_library(${module} STATIC ${src_list})
            set_target_properties(${module} PROPERTIES
                POSITION_INDEPENDENT_CODE ON)
            target_include_directories(${module}
                PUBLIC
                    ${module}
                    ${CMAKE_CURRENT_SOURCE_DIR}/common)
            if(EXISTS ${module_dir}/dependencies.cmake)
                include(${module_dir}/dependencies.cmake)
                add_dependencies(${module} ${MODULE_DEPS})
                target_include_directories(${module} PUBLIC ${MODULE_DEPS})
                target_link_libraries(${module}
                    PUBLIC
                        ${MODULE_DEPS}
                        ${system_libs}
                        common)
                    message(STATUS "add dependencies from ${module} to ${MODULE_DEPS}")
            endif()
            unset(src_list)
        endif()

        if(IS_DIRECTORY ${module_dir}/test/)
            file(GLOB src_list ${module_dir}/test/*.cpp)
            foreach(src_file ${src_list})
                get_filename_component(exec ${src_file} NAME_WE)
                message(STATUS "build exec ${exec}")
                add_executable(${exec} ${src_file})
                add_dependencies(${exec} common)
                target_link_libraries(${exec}
                    PUBLIC
                        ${module}
                        common
                        ${system_libs})
                target_include_directories(${exec}
                    PUBLIC
                        ${CMAKE_CURRENT_SOURCE_DIR}/common)
                add_test(
                    NAME ${exec}
                    COMMAND ${exec}
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
            endforeach()
        endif()
    endif()
endforeach()
