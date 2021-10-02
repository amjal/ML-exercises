add_library(DataManager DataManager.cpp)
target_include_directories(DataManager PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/csv-parser/single_include")