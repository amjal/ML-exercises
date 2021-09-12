cmake_minimum_required(VERSION 3.20)
project(ML_exercises)

set(CMAKE_CXX_STANDARD 14)

add_executable(ML_exercises
        chapter2/assignment2.cpp
        chapter2/assignment3.cpp
        chapter4/assignment1/main.cpp
        chapter4/example.h
        chapter4/main.cpp
        chapter4/PolynomialClassifier.cpp
        chapter4/PolynomialClassifier.h
        )

# Add the file handler library
add_subdirectory(libfile)
# Link the executable to the library
target_link_libraries("${PROJECT_NAME}" PUBLIC libfile)
# Add binaries to the search path of the include files
target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/libfile")

# Include other directories containing cpp files
include_directories(.)
include_directories(chapter4)
