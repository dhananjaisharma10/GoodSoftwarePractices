/**
 * An example of the Don't Repeat Yourself (DRY) principle
 *
 * We would like to write a Worker class which can support 2 types of
 * functionalities depending on some helper. The simplest solution is to just
 * write 2 different classes, but if there is reasonable overlap for the 2
 * versions of the worker, we could make use of the DRY principle.
 *
 * In this example, we have 2 helper classes for a Worker class.
 * Both helpers provide slightly different functionalities to the worker.
 * I have used dependency injection to pass the helper object to the worker.
 * In addition, the worker has different parameters depending on the
 * helper. I have made use of the std::optional feature for the same.
 */

#include <iostream>
#include <memory>
#include <optional>
#include <vector>

class HelperInterface {
public:
  HelperInterface() = default;
  virtual ~HelperInterface() = default;
  virtual void compute(const std::vector<float> &inputs,
                       std::vector<float> &outputs) const = 0;
};

class FooHelper : public HelperInterface {
public:
  FooHelper() = default;
  ~FooHelper() override {}

  void compute(const std::vector<float> &inputs,
               std::vector<float> &outputs) const override {
    for (size_t i = 1; i < outputs.size(); i++) {
      outputs[i] += inputs[i - 1];
    }
  }
};

class BooHelper : public HelperInterface {
public:
  BooHelper() = default;
  ~BooHelper() override {}

  void compute(const std::vector<float> &inputs,
               std::vector<float> &outputs) const override {
    for (size_t i = 1; i < outputs.size(); i++) {
      outputs[i] += inputs[i - 1] * 2;
    }
  }
};

class Worker {
public:
  // Dependency injection for HelperInterface
  Worker(std::unique_ptr<HelperInterface>&& helper)
      : helper_{std::move(helper)} {}

  std::vector<float> doSomething(const std::vector<float> &input) const {
    auto output{input};
    helper_->compute(input, output);
    return output;
  }

private:
  std::unique_ptr<HelperInterface> helper_;
};

void printVec(const std::vector<float> &vec) {
  for (const auto n : vec) {
    std::cout << n << " ";
  }
  std::cout << std::endl;
}

int main() {
  auto fooHelper = std::make_unique<FooHelper>();
  auto booHelper = std::make_unique<BooHelper>();

  Worker fooWorker{std::move(fooHelper)};
  Worker booWorker{std::move(booHelper)};

  const std::vector<float> input{1, 2, 3, 4};

  auto fooOut = fooWorker.doSomething(input);
  auto booOut = booWorker.doSomething(input);

  // The expected result would be different for both outputs, depending on
  // the injected helper object.
  printVec(fooOut);
  printVec(booOut);

  return EXIT_SUCCESS;
}