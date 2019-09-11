cmake_minimum_required(VERSION 3.13)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ImageProcessing main.cpp ImageProcessor.h ImageProcessor.cpp)