cmake_minimum_required(VERSION 3.20)
project(ML_exercises)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(chapter4)

add_executable(ML_exercises
        chapter2/assignment2.cpp
        chapter2/assignment3.cpp
        chapter4/assignment1/main.cpp
        chapter4/example.h
        chapter4/main.cpp
        chapter4/PolynomialClassifier.cpp
        chapter4/PolynomialClassifier.h
        cpp_csv_handler.cpp
        cpp_csv_handler.h
        )
