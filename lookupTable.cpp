#include <cstdint>
#include <iostream>

uint16_t forwardTable[65536];
uint16_t reverseTable[65536];
uint16_t resetMasks[4] {
    0xFFF0,
    0xFF0F,
    0xF0FF,
    0x0FFF
};

int getMask(const uint16_t row, const int pos) {
    return (row & (0xF << (pos << 2))) >> (pos << 2);
}

// somehow this shit works
void populateForwardTable() {
    forwardTable[0] = 0;
    for (int i {1}; i < 65536; ++i) {
        // row
        int nextEmptyPosition {-1};
        int lastValue {-1};
        int lastValueIndex {-1};
        uint16_t row {static_cast<uint16_t>(i)};

        //std::cout << "Initial row --> " << std::hex << row << '\n';

        for (int j {0}; j < 4; ++j) {
            int value {getMask(row, j)};
            if (!value) {
                nextEmptyPosition = (nextEmptyPosition == -1) ? j : nextEmptyPosition;
            } else if (value == lastValue) {
                lastValue = (lastValue == 0xF) ? 0xF : lastValue+1;
                // zero tile first
                row &= resetMasks[j];
                row &= resetMasks[lastValueIndex];

                //std::cout << "Row after zeroing both tiles before merging --> " << std::hex << row << '\n';

                // set to incremented value
                row |= (lastValue << (lastValueIndex << 2));

                //std::cout << "Row after merging --> " << std::hex << row << '\n';

                nextEmptyPosition = lastValueIndex+1;
                lastValue = -1;
                lastValueIndex = -1;
            } else {
                lastValue = value;
                lastValueIndex = j;
                if (nextEmptyPosition != -1) {
                    row |= value << (nextEmptyPosition * 4);
                    row &= resetMasks[j];
                    //
                    //value >>= (j - lastValueIndex)*4;
                    //row |= value;
                    lastValueIndex = nextEmptyPosition;
                    ++nextEmptyPosition;
                }
            }
        }        
        forwardTable[i] = row;
        std::cout << std::hex << i << " --> " << forwardTable[i] << '\n';
    }
}

void populateReverseTable() {
    reverseTable[0] = 0;
    for (int i {1}; i < 65536; ++i) {
        // row
        int nextEmptyPosition {-1};
        int lastValue {-1};
        int lastValueIndex {-1};
        uint16_t row {static_cast<uint16_t>(i)};

        //std::cout << "Initial row --> " << std::hex << row << '\n';

        for (int j {3}; j >= 0; --j) {
            int value {getMask(row, j)};
            if (!value) {
                nextEmptyPosition = (nextEmptyPosition == -1) ? j : nextEmptyPosition;
            } else if (value == lastValue) {
                lastValue = (lastValue == 0xF) ? 0xF : lastValue+1;
                // zero tile first
                row &= resetMasks[j];
                row &= resetMasks[lastValueIndex];

                //std::cout << "Row after zeroing both tiles before merging --> " << std::hex << row << '\n';

                // set to incremented value
                row |= (lastValue << (lastValueIndex << 2));

                //std::cout << "Row after merging --> " << std::hex << row << '\n';

                nextEmptyPosition = lastValueIndex-1;
                lastValue = -1;
                lastValueIndex = -1;
            } else {
                lastValue = value;
                lastValueIndex = j;
                if (nextEmptyPosition != -1) {
                    row |= value << (nextEmptyPosition * 4);
                    row &= resetMasks[j];
                    //
                    //value >>= (j - lastValueIndex)*4;
                    //row |= value;
                    lastValueIndex = nextEmptyPosition;
                    --nextEmptyPosition;
                }
            }
        }        
        reverseTable[i] = row;
        std::cout << std::hex << i << " --> " << reverseTable[i] << '\n';
    }

}

// bugged as shit
void printMoveRow() {
    for (uint16_t i {0}; i < 65536; ++i) {
        for (int j {0}; j < 4; ++j) {
            // isolate that tile
            int val {i & ~resetMasks[j]};
            // shift to right
            val >>= (j*4);
            val = 0x1 << val;
            val = (val == 1) ? 0 : val;
            std::cout << val << "  ";
        }
        std::cout << "--->   ";

        uint16_t newRow {forwardTable[i]};
        for (int j {0}; j < 4; ++j) {
            // isolate that tile
            int val {newRow & ~resetMasks[j]};
            // shift to right
            val >>= (j*4);
            val = 0x1 << val;
            val = (val == 1) ? 0 : val;
            std::cout << val << "  ";
        }
        std::cout << "\n";
    }
}

int main() {
    populateForwardTable();
    populateReverseTable();
    //printMoveRow();
    /* 
    for (int i {0}; i < 65536; ++i) {
        std::cout << forwardTable[i] << '\n';
    }
    */
    return 0;
}