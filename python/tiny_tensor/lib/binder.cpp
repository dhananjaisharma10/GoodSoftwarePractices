#include "tensor.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

PYBIND11_MODULE(tiny_tensor, m) {
  pybind11::class_<tn::Tensor>(m, "Tensor")
      .def(pybind11::init<const std::vector<float> &>())
      .def("get_size", &tn::Tensor::getSize);
  m.doc() = "A tiny tensor library";
}
