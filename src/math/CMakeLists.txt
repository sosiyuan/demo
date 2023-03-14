message("Build Math lib")
include_directories(./inc)

aux_source_directory(./src src_files)
add_library(my_math SHARED ${src_files})
add_dependencies(${TARGET_NAME} my_math)
