cmake_minimum_required (VERSION 3.10)
project (misc)

set(CMAKE_CXX_STANDARD 14)

file(GLOB modules ${CMAKE_CURRENT_LIST_DIR}/*)

foreach (module_dir ${modules})
    if (IS_DIRECTORY ${module_dir})
        get_filename_component(module ${module_dir} NAME)
        file (GLOB_RECURSE src_list ${module}/*.cpp)
        if (src_list)
            message(STATUS "build module ${module}")
            add_library (${module} SHARED ${src_list})
            target_include_directories (${module} PUBLIC ${module})
            unset (src_list)
        endif()
    endif()
endforeach()
