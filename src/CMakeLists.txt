target_sources(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src_main.cpp)

add_subdirectory(./math)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/math/inc)
target_link_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)