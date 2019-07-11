#include <random>

class randomNum {
public:
    static int getRandomNum(int range);
private:
    static std::mt19937 rng; 
};