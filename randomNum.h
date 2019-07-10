#include <random>

class randomNum {
private:
    static std::mt19937 rng; 
public:
    static int getRandomNum(int range);
};