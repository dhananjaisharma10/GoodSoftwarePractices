#include "tensor.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

PYBIND11_MODULE(tiny_tensor, m) {
  pybind11::class_<tn::Tensor>(m, "Tensor")
      .def(pybind11::init<const std::vector<float> &>())
      .def("size", &tn::Tensor::getSize)
      .def("data", &tn::Tensor::data)
      .def("__getitem__", &tn::Tensor::at)
      .def("__truediv__", &tn::Tensor::scalarDiv)
      .def("__mul__", &tn::Tensor::scalarMul)
      .def("__imul__", &tn::Tensor::selfScalarMul)
      .def("__add__", &tn::Tensor::scalarAdd)
      .def("__iadd__", &tn::Tensor::selfScalarAdd)
      .def("__sub__", &tn::Tensor::scalarSub)
      .def("__isub__", &tn::Tensor::selfScalarSub)
      .def("__eq__", &tn::Tensor::isEqual)
      .def("tensor_add", &tn::Tensor::tensorAdd)
      .def("tensor_mul", &tn::Tensor::tensorMul);
  m.doc() = "A tiny tensor library";
}
