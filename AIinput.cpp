#include <map>
#include <algorithm>
#include "AIinput.h"
#include "Board.h"
#include "randomNum.h"

AIinput::AIinput() : gameBoard {nullptr}, iterationsPerMove {2000} {}

AIinput::AIinput(int n) : gameBoard {nullptr}, iterationsPerMove {n} {}

void AIinput::assignBoard(Board* b) {
    gameBoard = b;
}

/* For each move direction, makes that move then plays many game simulations using 
 * random moves and averages their final scores. Then selecting the move with the
 * highest average score
 */
char AIinput::input() const {
    std::map<char, double> moveAverages {{'u', 0.0}, {'d', 0.0}, {'r', 0.0}, {'l', 0.0}};
    for (auto& move : moveAverages) {
        move.second = getAverage(move.first);
    }
    auto maxVal {std::max_element(
        moveAverages.begin(), moveAverages.end(),
        [] (const std::pair<char, double>& p1, const std::pair<char, double>& p2) {
            return p1.second < p2.second;
        }
    )};
    return maxVal->first;
}

double AIinput::getAverage(char move) const {
    double scoreTally {0};
    for (int i {0}; i < iterationsPerMove; ++i) {
        Board boardCopy {*gameBoard};
        if (boardCopy.moveBoard(move)) {
            boardCopy.placeRandomTile();
            scoreTally += simGame(boardCopy);
        // that move is not possible, skip simulations for that move 
        } else {
            return -1;
        }
    }
    return scoreTally / iterationsPerMove;
}

long AIinput::simGame(Board& board) const {
    while (true) {
        int rand {randomNum::getRandomNum(3)};
        char m;
        switch (rand) {
            case 0: m = 'u'; break;
            case 1: m = 'd'; break;
            case 2: m = 'l'; break;
            case 3: m = 'r'; break;
            default: throw "Random number in simGame not in correct range\n";
        }
        if (board.moveBoard(m)) {
            board.placeRandomTile();
        } 
        if (board.isGameOver()) {
            return board.score();
        }
    }
}