cmake_minimum_required(VERSION 3.0.0)
project(test-cpp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PREBUILT_MODULE_PATH ${CMAKE_BINARY_DIR}/modules)

function(add_module name)
    file(MAKE_DIRECTORY ${PREBUILT_MODULE_PATH})
    add_custom_target(
        ${name}.pcm
        COMMAND
            ${CMAKE_CXX_COMPILER}
            -std=c++20
            -c
            ${CMAKE_CURRENT_SOURCE_DIR}/${ARGN}
            -Xclang -emit-module-interface
            -o ${PREBUILT_MODULE_PATH}/${name}.pcm
    )
endfunction()

add_compile_options(-fprebuilt-module-path=${PREBUILT_MODULE_PATH})

add_module(networks networks.cc)
add_executable(test-cpp main.cpp networks.cc)
add_dependencies(test-cpp networks.pcm)
