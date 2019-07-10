#include <random>
#include "randomNum.h"

std::mt19937 randomNum::rng {std::random_device{}()};

int randomNum::getRandomNum(int range) {
    return std::uniform_int_distribution<int>{0, range}(rng);
}