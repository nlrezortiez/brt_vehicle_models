cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(car_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

add_executable(${CMAKE_PROJECT_NAME} test.cc)
add_compile_definitions(KBM)