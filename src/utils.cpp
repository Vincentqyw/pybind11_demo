#include <string>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <opencv2/opencv.hpp>
#include "include/utils.h"

namespace py = pybind11;

cv::Mat numpy_to_mat(py::array_t<uint8_t> input) {
    py::buffer_info buf = input.request();
    cv::Mat mat(buf.shape[0], buf.shape[1], CV_8UC3, (uint8_t*)buf.ptr);
    return mat.clone();
}

py::array_t<uint8_t> mat_to_numpy(const cv::Mat &mat) {
    py::array_t<uint8_t> array(
        {mat.rows, mat.cols, mat.channels()},
        mat.data);
    return array;
}

void BindFeatureType(py::module &m) {
    py::enum_<FeatureType>(m, "FeatureType")
    .value("HOG", FeatureType::HOG)
    .value("SIFT", FeatureType::SIFT)
    .value("SURF", FeatureType::SURF)
    .value("SP", FeatureType::SP)
    .export_values();
}

void BindOptions(py::module &m) {
    py::class_<options>(m, "options")
        .def(py::init<>())
        .def_readwrite("filename", &options::filename)
        .def_readwrite("params", &options::params)
        .def_property("image",
            [](options &o) { return mat_to_numpy(o.image); },
            [](options &o, py::array_t<uint8_t> img) { o.image = numpy_to_mat(img); });
}
