#include <random>
#include "randomNum.h"

int getRandomNum(std::size_t range) {
    std::random_device d;
    std::mt19937 rng(d());
    std::uniform_int_distribution<std::mt19937::result_type> num(0, range);
    return num(rng);
}