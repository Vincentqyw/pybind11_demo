#include <string>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <opencv2/opencv.hpp>

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

struct options
{
    cv::Mat image;
    std::string filename;
    std::vector<float> params;
    std::shared_ptr<float> params2;
};


class ImageProcessor {
public:
    ImageProcessor(const std::string &config);
    ~ImageProcessor();
    cv::Mat process(const options &opts);
private:
    std::shared_ptr<float*> params;
    std::shared_ptr<cv::Mat> p_img;
};

ImageProcessor::ImageProcessor(const std::string &config) {
    // demo inputs
    params = std::make_shared<float*>(new float[10]);
    const std::string &img_path = "/workspaces/pybind11_demo/demo/93341989_396310999.jpg";
    cv::Mat img = cv::imread(img_path, cv::IMREAD_UNCHANGED);
    p_img = std::make_shared<cv::Mat>(img);
}

cv::Mat ImageProcessor::process(const options &opts) {
    return *p_img;
}

ImageProcessor::~ImageProcessor() {
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

void BindImageProcessor(py::module &m) {
    py::class_<ImageProcessor>(m, "ImageProcessor")
        .def(py::init<const std::string &>())
        .def("process", [](ImageProcessor &self, const options &opts) {
            return mat_to_numpy(self.process(opts));
        });
}

PYBIND11_MODULE(binding_demo, m) {
    m.doc() = "pybind11 demo plugin";
    BindOptions(m);
    BindImageProcessor(m);
}
