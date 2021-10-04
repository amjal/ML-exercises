# Add new target
add_library(DataManager DataManager.hpp)
# Specify the language of the target because it is .hpp and not automatically recognizable
set_target_properties(DataManager PROPERTIES LINKER_LANGUAGE CXX)
# Add include search directories for the library
target_include_directories(DataManager PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/csv-parser/single_include")