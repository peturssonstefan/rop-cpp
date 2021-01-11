cmake_minimum_required(VERSION 3.10)

project(rop)

add_subdirectory(roplib)

add_executable(rop main.cc datalayer.cc businesslayer.cc)


target_include_directories(rop PUBLIC 
						   "${PROJECT_BINARY_DIR}"
						   "${PROJECT_SOURCE_DIR}/roplib")

target_link_libraries(rop PUBLIC roplib)

target_link_libraries(rop PUBLIC roplib)

