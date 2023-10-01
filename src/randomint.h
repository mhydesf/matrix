#pragma once

#include <random>

namespace Matrix::Utility {

class RandomInt {
public:
    RandomInt(int min, int max)
        : distribution(min, max) {
        generator.seed(std::random_device()());
    }

    int GetRandomInt() {
        return distribution(generator);
    }

private:
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
};

} // namespace Matrix::Utility
