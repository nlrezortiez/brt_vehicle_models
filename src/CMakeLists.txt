add_executable(${CMAKE_PROJECT_NAME} test.cc)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${BRT_INCLUDE_DIR})