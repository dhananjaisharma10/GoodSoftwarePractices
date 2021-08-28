/**
 * This file describes an example to follow the Don't Repeat Yourself
 * (DRY) principle
 */

#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

// TODO: Change the variable names, make them generic.
// TODO: Describe what the problem is, and how we are going to solve it.

class DecoderInterface {
public:
  DecoderInterface() = default;
  virtual ~DecoderInterface() = default;
  virtual void decodeDetections(const std::vector<float> &preds,
                                std::vector<float> &outputs) const = 0;
};

class DecoderFoo : public DecoderInterface {
public:
  DecoderFoo() = default;
  ~DecoderFoo() override {}

  void decodeDetections(const std::vector<float> &preds,
                        std::vector<float> &outputs) const override {
    for (size_t i = 1; i < outputs.size(); i++) {
      outputs[i] += preds[i - 1];
    }
  }
};

class DecoderBoo : public DecoderInterface {
public:
  DecoderBoo() = default;
  ~DecoderBoo() override {}

  void decodeDetections(const std::vector<float> &preds,
                        std::vector<float> &outputs) const override {
    for (size_t i = 1; i < outputs.size(); i++) {
      outputs[i] += preds[i - 1] * 2;
    }
  }
};

class Detector {
public:
  struct Params {
    int height{};
    int width{};
    std::optional<bool> frontFacing;
  };

  Detector(Params params, std::unique_ptr<DecoderInterface> decoder)
      : params_{std::move(params)}, decoder_{std::move(decoder)} {}

  std::vector<float> process(const std::vector<float> &input) const {
    auto output{input};
    decoder_->decodeDetections(input, output);
    return output;
  }

private:
  Params params_;
  std::unique_ptr<DecoderInterface> decoder_;
};

void printVec(const std::vector<float> &vec) {
  for (const auto n : vec) {
    std::cout << n << " ";
  }
  std::cout << std::endl;
}

int main() {
  Detector::Params paramsFoo{100, 200};
  Detector::Params paramsBoo{100, 200, true};
  auto decoderFoo = std::make_unique<DecoderFoo>();
  auto decoderBoo = std::make_unique<DecoderBoo>();
  Detector foo{paramsFoo, std::move(decoderFoo)};
  Detector boo{paramsBoo, std::move(decoderBoo)};

  const std::vector<float> input{1, 2, 3, 4};

  auto fooOut = foo.process(input);
  auto booOut = boo.process(input);

  printVec(fooOut);
  printVec(booOut);

  return EXIT_SUCCESS;
}