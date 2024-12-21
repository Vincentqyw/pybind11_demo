#ifndef _PYBIND11_TESTS_UTILS_H_
#define _PYBIND11_TESTS_UTILS_H_

#include <string>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <opencv2/opencv.hpp>

namespace py = pybind11;

cv::Mat numpy_to_mat(py::array_t<uint8_t> input);
py::array_t<uint8_t> mat_to_numpy(const cv::Mat &mat);

enum FeatureType {
    HOG = 0,
    SIFT = 1,
    SURF = 2,
    SP = 3
};

struct options
{
    cv::Mat image;
    std::string filename;
    std::vector<float> params;
    FeatureType feature_type;
};

#endif
