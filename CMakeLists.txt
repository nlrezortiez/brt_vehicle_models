cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(car_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

set(BRT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(BRT_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

if(DEFINED DBM)
    add_compile_definitions(DBM)
endif()

add_subdirectory(${BRT_SRC_DIR})