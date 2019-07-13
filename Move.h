#ifndef MOVE_H
#define MOVE_H

template <typename Move>
void reset(Move& move) {
    move.nextFreeSlot = -1;
    move.previousTile = -1;
    move.previousTileValue = -1;
}

struct Right {
    static constexpr int start {15};
    int nextFreeSlot;
    int previousTile;
    int previousTileValue;

    Right() {
        reset(*this);
    }

    static constexpr bool end(int index) {
        return index >= 0;
    }
    static constexpr int step(int index) {
        return index-1;
    }
    static constexpr bool test(int index) {
        return index % 4 == 0;
    }
};

struct Left {
    static constexpr int start {0};
    int nextFreeSlot;
    int previousTile;
    int previousTileValue;

    Left() {
        reset(*this);
    }

    static constexpr bool end(int index) {
        return index < 16;
    }
    static constexpr int step(int index) {
        return index+1;
    }
    static constexpr bool test(int index) {
        return (index + 1) % 4 == 0;
    }
};

struct Up {
    static constexpr int start {0};
    int nextFreeSlot;
    int previousTile;
    int previousTileValue;

    Up() {
        reset(*this);
    }

    static constexpr bool end(int index) {
        return index < 16;
    }
    static constexpr int step(int index) {
        if (index == 15) return 16;
        return (index > 11) ? (index - 11) : index + 4;
    }
    static constexpr bool test(int index) {
        return index > 11;
    }
};

struct Down {
    static constexpr int start {15};
    int nextFreeSlot;
    int previousTile;
    int previousTileValue;

    Down() {
        reset(*this);
    }

    static constexpr bool end(int index) {
        return index >= 0;
    }
    static constexpr int step(int index) {
        if (index == 0) return -1;
        return (index < 4) ? (index + 11) : index - 4;
    }
    static constexpr bool test(int index) {
        return index < 4;
    }
};

#endif