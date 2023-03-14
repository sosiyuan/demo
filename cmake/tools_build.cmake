message(" ========= Build Sub Product ========= ")

add_subdirectory(${CMAKE_SOURCE_DIR}/dependency/tools)
add_dependencies(${TARGET_NAME} tools)