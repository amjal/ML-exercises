cmake_minimum_required(VERSION 3.20)
project(ML_exercises)

set(CMAKE_CXX_STANDARD 14)
#set(COMPILE_FLAGS "-O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")

add_executable(ML_exercises
        chapter2/assignment2.cpp)
#        chapter2/assignment3.cpp
#        chapter4/assignment1/main.cpp
#        chapter4/example.h
#        chapter4/main.cpp
#        chapter4/PolynomialClassifier.cpp
#        chapter4/PolynomialClassifier.h
#        )

add_subdirectory(csv-parser)
target_link_libraries("${PROJECT_NAME}" PUBLIC csv)
target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/csv-parser/single_include")

# Add the file handler library
add_subdirectory(data-manager)
# Link the executable to the library
target_link_libraries("${PROJECT_NAME}" PUBLIC DataManager)
# Add binaries to the search path of the include files
target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/data-manager")

# Include other directories containing cpp files
include_directories(.)
include_directories(chapter4)
