#include <cstdlib>
#include <memory>

/**
 * Constructor dependency injection
 */

class Dependency {
public:
  virtual ~Dependency() = default;
  virtual void doSomething() const = 0;
};

class FooDependency : public Dependency {
public:
  FooDependency() = default;
  void doSomething() const override {}
};

class BooDependency : public Dependency {
public:
  BooDependency() = default;
  void doSomething() const override {}
};

class Worker {
public:
  /**
   * dep: Injecting the dependency through a unique pointer
   */
  Worker(std::unique_ptr<Dependency> &&dep) : dep_{std::move(dep)} {
    if (dep_ == nullptr) {
      throw std::invalid_argument("[Worker::Worker] dep_ must not be null");
    }
  }

private:
  std::unique_ptr<Dependency> dep_;
};

int main() {
  auto fooDep = std::make_unique<FooDependency>();
  auto booDep = std::make_unique<BooDependency>();

  auto fooWorker = Worker(std::move(fooDep));
  auto booWorker = Worker(std::move(booDep));

  return EXIT_SUCCESS;
}
