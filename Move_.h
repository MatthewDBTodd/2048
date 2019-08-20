struct Forward {
    int nextEmptyPosition {-1};
    int lastValue {-1};
    int lastValueIndex {-1};

    static constexpr int start {0};
    bool end(int i) { return i < 4; }
    int next(int i) { return i+1; }
};

struct Reverse {
    int nextEmptyPosition {-1};
    int lastValue {-1};
    int lastValueIndex {-1};

    static constexpr int start {3};
    bool end(int i) { return i >= 0; }
    int next(int i) { return i-1; }
};