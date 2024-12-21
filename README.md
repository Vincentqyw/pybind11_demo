# small demo for pybind11

An example [pybind11](https://github.com/pybind/pybind11) module built with a
CMake-based build system. This is useful for C++ codebases that have an
existing CMake project structure.


## Prerequisites

* A compiler with C++11 support
* Pip 10+ or CMake >= 3.4 (or 3.14+ on Windows, which was the first version to support VS 2019)
* Ninja or Pip 10+
* OpenCV >= 3.4

``` bash
sudo apt-get update
sudo apt-get install libopencv-dev -y
```

## Installation

Just clone this repository and pip install. Note the `--recursive` option which is
needed for the pybind11 submodule:

```bash
git clone --recursive https://github.com/Vincentqyw/pybind11_demo
cd pybind11_demo
pip install .

# Alternatively, install in editable mode
pip install -e .
```

With the `setup.py` file included in this example, the `pip install` command will
invoke CMake and build the pybind11 module as specified in `CMakeLists.txt`.

## Test

```bash
python -m pytest
```

## Format code

```bash
pre-commit run -a  # pip install pre-commit
```

## License

Pybind11 is provided under a BSD-style license that can be found in the LICENSE
file. By using, distributing, or contributing to this project, you agree to the
terms and conditions of this license.
