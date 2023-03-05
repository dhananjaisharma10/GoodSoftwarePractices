# Tiny Tensor

## Introduction

Tiny Tensor is a small library wrapping a `tn::Tensor` class, written in CPP, for use in Python.

It was done as a learning exercise to get comfortable with `pybind11`, and to get a feel of how libraries like PyTorch are implemented using Cpp and have Python bindings.

## Requirements

Please create a virtual environment before proceeding.

You can install `pybind11` through the various methods mentioned in the [official documentation](https://pybind11.readthedocs.io/en/stable/installing.html).

## Usage

**Note**: The instructions are MacOS-specific. Please use Python 3.9.

You need to compile the CPP code to create the Python-importable library using the following instruction.

```bash
c++ -O3 -Wall -shared -std=c++17 -undefined dynamic_lookup $(python3 -m pybind11 --includes) tiny_tensor/lib/binder.cpp -o tiny_tensor/tiny_tensor$(python3-config --extension-suffix)
```

Source: [Build systems - building manually](https://pybind11.readthedocs.io/en/stable/compiling.html#building-manually) from pybind11 documentation.

As a result, you should get the following file: `tiny_tensor.cpython-39-darwin.so` in the `tiny_tensor/` folder. This file is importable as a Python module - `import tiny_tensor`.

Then, you can run the `test.py` module, which calls the CPP code through the binding, as follows:

```bash
python test.py
```
