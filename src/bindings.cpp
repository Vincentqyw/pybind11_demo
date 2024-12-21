#include "include/utils.h"

namespace py = pybind11;

void BindFeatureType(py::module &m);
void BindOptions(py::module &m);
void BindForwardType(py::module &m);
void BindImageProcessor(py::module &m);

PYBIND11_MODULE(binding_demo, m) {
    /**
     * @brief Python binding module for the library
     *
     * This module exports the Options and ImageProcessor classes, which are
     * used to interface with the library.
     */
#ifdef VERSION_INFO
    m.attr("__version__") = py::str(VERSION_INFO);
#else
    m.attr("__version__") = py::str("dev");
#endif
    // Add a docstring to the module
    m.doc() = "pybind11 demo plugin";
    // Export the Options and ImageProcessor classes
    BindFeatureType(m);
    BindOptions(m);
    BindForwardType(m);
    BindImageProcessor(m);
}
