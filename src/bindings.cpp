#include <string>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <opencv2/opencv.hpp>
#include "include/utils.h"

namespace py = pybind11;

class ImageProcessor {
public:
    ImageProcessor(const std::string &config, const std::string &img_path);
    ~ImageProcessor();
    cv::Mat process(const options &opts);
private:
    std::shared_ptr<float*> params;
    std::shared_ptr<cv::Mat> p_img;
};

ImageProcessor::ImageProcessor(const std::string &config, const std::string &img_path) {
    // demo inputs
    params = std::make_shared<float*>(new float[10]);
    cv::Mat img = cv::imread(img_path, cv::IMREAD_UNCHANGED);
    p_img = std::make_shared<cv::Mat>(img);
}

cv::Mat ImageProcessor::process(const options &opts) {
    return *p_img;
}

ImageProcessor::~ImageProcessor() {
}

void BindFeatureType(py::module &m);
void BindOptions(py::module &m);

void BindImageProcessor(py::module &m) {
    py::class_<ImageProcessor>(m, "ImageProcessor")
        .def(py::init<const std::string &, const std::string &>())
        .def("process", [](ImageProcessor &self, const options &opts) {
            return mat_to_numpy(self.process(opts));
        });
}

PYBIND11_MODULE(binding_demo, m) {
#ifdef VERSION_INFO
    m.attr("__version__") = py::str(VERSION_INFO);
#else
    m.attr("__version__") = py::str("dev");
#endif
    m.doc() = "pybind11 demo plugin";
    BindOptions(m);
    BindImageProcessor(m);
}
