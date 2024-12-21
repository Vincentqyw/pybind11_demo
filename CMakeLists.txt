cmake_minimum_required(VERSION 3.12...3.18)
project(binding_demo)

set(OpenCV_DIR /usr/include/opencv4)
find_package(OpenCV REQUIRED)

add_subdirectory(pybind11)
file(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")
pybind11_add_module(binding_demo ${SOURCE_FILES})
target_include_directories(binding_demo PRIVATE ${OpenCV_INCLUDE_DIRS})
target_include_directories(binding_demo PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(binding_demo PRIVATE ${OpenCV_LIBS})
