#include <array>
#include <string>
#include <vector>

namespace tn {

class Tensor {
public:
  Tensor() = default;
  Tensor(const std::vector<float> &data) : _data(data) {}

  std::array<size_t, 1> getSize() const { return {_data.size()}; }

  const std::vector<float> &data() const { return _data; }

  float at(size_t index) const { return _data.at(index); }

  Tensor scalarDiv(float scalar) const {
    if (scalar == 0) {
      throw std::invalid_argument("Attempted vision by zero.");
    }
    std::vector<float> new_data(_data);
    // TODO: Use for_each here.
    for (auto &x : new_data) {
      x /= scalar;
    }
    return Tensor(new_data);
  }

  Tensor selfScalarDiv(float scalar) {
    // TODO: This method is still unused. Find the right dunder method for
    // division and call it.
    // TODO: Use for_each here.
    for (auto &x : _data) {
      x /= scalar;
    }
    return *this;
  }

  Tensor scalarMul(float scalar) const {
    std::vector<float> new_data(_data);
    // TODO: Use for_each here.
    for (auto &x : new_data) {
      x *= scalar;
    }
    return Tensor(new_data);
  }

  Tensor selfScalarMul(float scalar) {
    // TODO: Use for_each here.
    for (auto &x : _data) {
      x *= scalar;
    }
    return *this;
  }

  Tensor scalarAdd(float scalar) const {
    std::vector<float> new_data(_data);
    // TODO: Use for_each here.
    for (auto &x : new_data) {
      x += scalar;
    }
    return Tensor(new_data);
  }

  Tensor selfScalarAdd(float scalar) {
    // TODO: Use for_each here.
    for (auto &x : _data) {
      x += scalar;
    }
    return *this;
  }

  Tensor scalarSub(float scalar) const {
    std::vector<float> new_data(_data);
    // TODO: Use for_each here.
    for (auto &x : new_data) {
      x -= scalar;
    }
    return Tensor(new_data);
  }

  Tensor selfScalarSub(float scalar) {
    // TODO: Use for_each here.
    for (auto &x : _data) {
      x -= scalar;
    }
    return *this;
  }

  Tensor tensorAdd(const Tensor &other) const {
    if (!hasSameSize(other)) {
      throw std::invalid_argument("Size mismatch error.");
    }

    std::vector<float> new_data(_data);
    const auto &other_data = other.data();
    // TODO: Use for_each here.
    for (size_t i = 0; i < _data.size(); i++) {
      new_data[i] += other_data[i];
    }
    return Tensor(new_data);
  }

  Tensor tensorMul(const Tensor &other) const {
    if (!hasSameSize(other)) {
      throw std::invalid_argument("Size mismatch error.");
    }

    std::vector<float> new_data(_data);
    const auto &other_data = other.data();
    // TODO: Use for_each here.
    for (size_t i = 0; i < _data.size(); i++) {
      new_data[i] *= other_data[i];
    }
    return Tensor(new_data);
  }

  bool isEqual(const Tensor &other) {
    if (!hasSameSize(other)) {
      return false;
    }

    for (size_t i = 0; i < _data.size(); i++) {
      if (_data[i] != other.data()[i]) {
        return false;
      }
    }

    return true;
  }

private:
  bool hasSameSize(const Tensor &other) const {
    return _data.size() == other.data().size();
  }

  std::vector<float> _data;
};

} // namespace tn
