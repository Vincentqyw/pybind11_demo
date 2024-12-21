#include <string>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <opencv2/opencv.hpp>
#include "include/utils.h"

namespace py = pybind11;

/**
 * @brief Convert a pybind11 numpy array to a cv::Mat object.
 *
 * @param input the numpy array to convert.
 * @return the converted cv::Mat object.
 */
cv::Mat numpy_to_mat(py::array_t<uint8_t> input) {
    // Retrieve the buffer information of the numpy array
    py::buffer_info buf = input.request();

    // Create a cv::Mat object from the buffer information.
    // The buffer information contains the shape of the numpy array,
    // and the pointer to the memory block which stores the numpy array.
    cv::Mat mat(buf.shape[0], buf.shape[1], CV_8UC3, (uint8_t*)buf.ptr);

    // The `clone()` function is used to make a copy of the cv::Mat object,
    // because the cv::Mat object is just a wrapper of the numpy array,
    // and the numpy array is managed by Python, so we must make a copy
    // of the cv::Mat object to ensure that the object is valid even after
    // the numpy array is released.
    return mat.clone();
}

/**
 * @brief Convert a cv::Mat object to a pybind11 numpy array.
 *
 * @param mat the cv::Mat object to convert.
 * @return the converted pybind11 numpy array.
 */
py::array_t<uint8_t> mat_to_numpy(const cv::Mat &mat) {
    // Create a pybind11 numpy array from the cv::Mat object.
    // The constructor of pybind11 numpy array takes a shape and a pointer to the memory block.
    // The shape is the shape of the cv::Mat object, and the pointer is the data pointer of the cv::Mat object.
    py::array_t<uint8_t> array(
        {mat.rows, mat.cols, mat.channels()}, // shape
        mat.data); // pointer to the memory block
    return array;
}

/**
 * @brief Construct an ImageProcessor object.
 *
 * @param config the configuration file for the image processing.
 * @param img_path the path to the image to be processed.
 */
ImageProcessor::ImageProcessor(const std::string &config, const std::string &img_path) {
    // demo inputs
    // create a shared pointer to a float array
    params = std::make_shared<float*>(new float[10]);
    // read the image from the given path
    cv::Mat img = cv::imread(img_path, cv::IMREAD_UNCHANGED);
    // create a shared pointer to the image
    p_img = std::make_shared<cv::Mat>(img);
}

/**
 * @brief Process an image according to the configuration and options.
 *
 * @param opts the options for the image processing.
 * @return the processed image.
 */
cv::Mat ImageProcessor::process(const options &opts) {
    // For now, just return the original image.
    // In the future, this function should be implemented to process the image
    // according to the configuration and options.
    return *p_img;
}

ForwardType ImageProcessor::forward(const options &opts) {
    // For now, just return the original image.
    // In the future, this function should be implemented to process the image
    // according to the configuration and options.
    ForwardType forward_output;
    forward_output.vbuffer_a = {1, 2, 3};
    forward_output.vvbuffer_b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    forward_output.vbuffer_c = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    return forward_output;
}


/**
 * @brief Destructor to free any resources used by the ImageProcessor.
 */
ImageProcessor::~ImageProcessor() {
    // Destructor implementation
    // Resource cleanup if needed
}

/**
 * @brief Binds the FeatureType enum to the given module.
 *
 * @param m the module to which the enum will be bound.
 */
void BindFeatureType(py::module &m) {
    // Create a pybind11 enum_ object for the FeatureType enum
    // and bind it to the module.
    py::enum_<FeatureType>(m, "FeatureType")
    // Assign each enum value to a corresponding Python value.
    .value("HOG", FeatureType::HOG, "Histogram of Oriented Gradients")
    .value("SIFT", FeatureType::SIFT, "Scale-Invariant Feature Transform")
    .value("SURF", FeatureType::SURF, "Speeded-Up Robust Features")
    .value("SP", FeatureType::SP, "Simple Precision")
    // Export the values of the enum.
    .export_values();
}

/**
 * @brief Binds the options class to the given module.
 *
 * @param m the module to which the class will be bound.
 */
void BindOptions(py::module &m) {
    // Create a pybind11 class_ object for the options class
    // and bind it to the module.
    py::class_<options> options_class(m, "options");

    // Add a docstring to the class
    options_class.doc() = "A class to represent options";

    // Add an __init__ method
    options_class.def(py::init<>());

    // Add readwrite properties
    options_class.def_readwrite("filename", &options::filename);
    options_class.def_readwrite("params", &options::params);

    // Add a property for the image
    options_class.def_property(
        "image",
        [](options &o) { // getter
            // Convert the image to a numpy array
            return mat_to_numpy(o.image);
        },
        [](options &o, py::array_t<uint8_t> img) { // setter
            // Convert the numpy array to an image
            o.image = numpy_to_mat(img);
        });
}

void BindForwardType(py::module &m) {
    py::class_<ForwardType>(m, "ForwardType")
        .def(py::init<>())
        .def_readwrite("vbuffer_a", &ForwardType::vbuffer_a)
        .def_readwrite("vvbuffer_b", &ForwardType::vvbuffer_b)
        .def_readwrite("vbuffer_c", &ForwardType::vbuffer_c);
}


/**
 * @brief Binds the ImageProcessor class to the given module.
 *
 * @param m the module to which the class will be bound.
 */
void BindImageProcessor(py::module &m) {
    // Create a pybind11 class_ object for the ImageProcessor class
    // and bind it to the module.
    py::class_<ImageProcessor> image_processor_class(m, "ImageProcessor");

    // Add a docstring to the class
    image_processor_class.doc() = "A class to process images";

    // Add an __init__ method
    image_processor_class.def(py::init<const std::string &, const std::string &>(),
                              py::arg("config"), py::arg("img_path"));

    // Add a process method
    image_processor_class.def("process", [](ImageProcessor &self, const options &opts) {
        // Call the process method on the ImageProcessor object
        // and convert the result to a numpy array
        return mat_to_numpy(self.process(opts));
    }, py::arg("opts"));

    // Add a forward method
    image_processor_class.def("forward", [](ImageProcessor &self, const options &opts) {
        // Call the forward method on the ImageProcessor object
        // and convert the result to a numpy array
        return self.forward(opts);
    }, py::arg("opts"));
}
