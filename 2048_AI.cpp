#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Game.h"
#include "AIinput.h"
#include "Score.h"

void saveScore(const Score& score) {
    std::ofstream outfile;
    outfile.open("scores.csv", std::ios_base::app);
    outfile << score.AIstrength << ',' << score.score << ',' <<
    score.highestTile << ',' << score.numTurns << '\n';
}

int getAIStrength(char *args[]) {
    std::string arg {args[1]};
    int n;
    try {
        std::size_t pos;
        n = std::stoi(arg, &pos);
        if (pos < arg.size()) {
            std::cout << "Invalid argument - only integers accepted with no trailing characters\n";
            return -1;
        }
    } catch (std::invalid_argument const &ex) {
        std::cout << "Invalid number: " << arg << '\n';
        return -1;
    } catch (std::out_of_range const &ex) {
        std::cout << "Number out of range: " << arg << '\n';
        return -1;
    }
    return n;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "./2048-AI [AI strength]\n";
        return 1;
    }
    int strength {getAIStrength(argv)};
    if (strength == -1) {
        return 1;
    }
    Game g(new AIinput(strength));
    Score score {g.play()};
    score.AIstrength = strength;
    saveScore(score);
    return 0;
}