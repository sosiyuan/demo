target_include_directories(${TARGET_NAME} PRIVATE .)
target_sources(${TARGET_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/creat_thread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/signal_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rw_mutex.cpp
)
