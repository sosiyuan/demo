CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(tools C CXX)
set(TARGET_NAME tools)

aux_source_directory(. src_files)
add_executable(${TARGET_NAME})

target_include_directories(${TARGET_NAME} PRIVATE ./)
target_sources(${TARGET_NAME} PRIVATE ${src_files})
