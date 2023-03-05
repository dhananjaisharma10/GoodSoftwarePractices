#include <vector>

namespace tn {

class Tensor {
public:
  Tensor() = default;
  Tensor(const std::vector<float> &data) : _data(data) {}

  const size_t getSize() const { return _data.size(); }

private:
  std::vector<float> _data;
};

} // namespace tn
