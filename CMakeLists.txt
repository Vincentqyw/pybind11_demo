cmake_minimum_required(VERSION 3.10)
project(imatchui)

set(OpenCV_DIR /usr/include/opencv4)
find_package(OpenCV REQUIRED)


add_subdirectory(pybind11)
pybind11_add_module(example src/bindings.cpp)
target_include_directories(example PRIVATE ${Boost_LIBRARIES} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(example PRIVATE ${OpenCV_LIBS})
