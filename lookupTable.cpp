#include <cstdint>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Move_.h"

uint16_t forwardTable[65536];
uint16_t reverseTable[65536]; 
int scoreTable[65536];
uint16_t resetMasks[4] {
    0xFFF0,
    0xFF0F,
    0xF0FF,
    0x0FFF
};

int getMask(const uint16_t row, const int pos) {
    return (row & ~resetMasks[pos]) >> (pos << 2);
}

template <typename T>
uint16_t merge(uint16_t row, int bitNum, T& move) {
    move.lastValue = (move.lastValue == 0xF) ? 0xF : move.lastValue+1;
    // zero tile
    row &= resetMasks[bitNum];
    row &= resetMasks[move.lastValueIndex];
    // set to incremented value
    row |= (move.lastValue << (move.lastValueIndex << 2));
    move.nextEmptyPosition = move.next(move.lastValueIndex);
    move.lastValue = -1;
    move.lastValueIndex = -1;
    return row;
}

template <typename T>
uint16_t swap(uint16_t row, int bitNum, int value, T& move) {
    row |= value << (move.nextEmptyPosition * 4);
    row &= resetMasks[bitNum];
    move.lastValueIndex = move.nextEmptyPosition;
    move.nextEmptyPosition = move.next(move.nextEmptyPosition);
    return row;
}

template <typename T>
uint16_t generateRow(uint16_t row, T& move) {
    for (int i {move.start}; move.end(i); i = move.next(i)) {
        int value {getMask(row, i)};
        if (!value) {
            move.nextEmptyPosition = (move.nextEmptyPosition == -1) ? i : move.nextEmptyPosition;
        } else if (value == move.lastValue) {
            row = merge(row, i, move);
        } else {
            move.lastValue = value;
            move.lastValueIndex = i;
            if (move.nextEmptyPosition != -1) {
                row = swap(row, i, value, move);
            }
        }
    }
    return row;
}

int generateScore(uint16_t row) {
    int score {0};
    char lastValue {0};
    for (int i {0}; i < 4; ++i) {
        char value = ((0xF << (i*4)) & row) >> (i*4);
        if (value == 0) { continue; }
        if (value == lastValue) {
            score += (0x1 << (value+1));
            lastValue = 0;
        } else {
            lastValue = value; 
        }
    }
    return score;
}

void populateTables() {
    for (int i {0}; i < 65536; ++i) {
        Forward f;
        Reverse r;
        uint16_t row {static_cast<uint16_t>(i)};
        forwardTable[i] = generateRow(row, f); 
        reverseTable[i] = generateRow(row, r);
        scoreTable[i] = generateScore(row);
    }
}

int main() {
    populateTables();
    std::ofstream out;
    out.open("table.txt");
    for (int i {0}; i < 65536; ++i) {
        out << std::setfill('0') << std::setw(4) << std::hex << i << '\n';
        out << "\tForward --> " << std::setfill('0') << std::setw(4) << std::hex << forwardTable[i] << '\n';
        out << "\tReverse --> " << std::setfill('0') << std::setw(4) << std::hex << reverseTable[i] << '\n';
        out << "\tScore ----> " << std::dec << scoreTable[i] << "\n\n";
    }
    return 0;
}