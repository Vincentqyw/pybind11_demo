cmake_minimum_required(VERSION 3.4...3.18)
project(binding_demo)

set(OpenCV_DIR /usr/include/opencv4)
find_package(OpenCV REQUIRED)

add_subdirectory(pybind11)
pybind11_add_module(binding_demo src/bindings.cpp)
target_include_directories(binding_demo PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(binding_demo PRIVATE ${OpenCV_LIBS})
