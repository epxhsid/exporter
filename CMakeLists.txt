cmake_minimum_required(VERSION 3.25)

project(
    fjord
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

add_executable(pexp
    src/main.cc
    src/cpu.cc
)

target_compile_features(pexp PRIVATE cxx_std_20)
target_include_directories(pexp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
