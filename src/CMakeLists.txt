add_executable(${CMAKE_PROJECT_NAME} driver.cc)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${BRT_INCLUDE_DIR})