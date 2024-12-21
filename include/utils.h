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

/**
 * @brief Structure to hold options for image processing.
 */
struct options {
    cv::Mat image;                  ///< Image to be processed
    std::string filename;           ///< Filename associated with the image
    std::vector<float> params;      ///< Parameters for processing
    FeatureType feature_type;       ///< Type of feature to be used
};

/**
 * @brief Structure to hold forward outputs.
 */
struct ForwardType {
    std::vector<uint8_t> vbuffer_a;
    std::vector<std::vector<uint8_t>> vvbuffer_b;
    std::vector<uint8_t> vbuffer_c;
};

/**
 * @brief ImageProcessor class to process images.
 *
 * This class takes a configuration file and an image path in its constructor.
 * The process method can then be used to process the image according to the
 * configuration and the options provided.
 */
class ImageProcessor {
public:
    /**
     * @brief Constructor to create an ImageProcessor object.
     *
     * @param config The configuration file for the image processing.
     * @param img_path The path to the image to be processed.
     */
    ImageProcessor(const std::string &config, const std::string &img_path);
    /**
     * @brief Destructor to free any resources used by the ImageProcessor.
     */
    ~ImageProcessor();
    /**
     * @brief Process an image according to the configuration and options.
     *
     * @param opts The options for the image processing.
     * @return The processed image.
     */
    cv::Mat process(const options &opts);

    /**
     * @brief Forward an image according to the configuration and options.
     *
     * @param opts The options for the image processing.
     * @return The forward outputs.
     */
    ForwardType forward(const options &opts);

private:
    std::shared_ptr<float*> params; ///< Parameters for processing
    std::shared_ptr<cv::Mat> p_img; ///< The image to be processed
    std::vector<uint8_t> vbuffer_a;
    std::vector<std::vector<uint8_t>> vvbuffer_b;
    std::vector<uint8_t> vbuffer_c;
};

#endif
