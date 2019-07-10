struct Right {
    static constexpr int start {15};
    static constexpr bool end(int index) {
        return index >= 0;
    }
    static constexpr int step(int index) {
        return index-1;
    }
    static constexpr bool test(int index) {
        return (index+1) % 4 == 0;
    }
    static constexpr int next(int index) {
        return index+1;
    }
};

struct Left {
    static constexpr int start {0};
    static constexpr bool end(int index) {
        return index < 16;
    }
    static constexpr int step(int index) {
        return index+1;
    }
    static constexpr bool test(int index) {
        return index % 4 == 0;
    }
    static constexpr int next(int index) {
        return index-1;
    }
};

struct Up {
    static constexpr int start {0};
    static constexpr bool end(int index) {
        return index < 16;
    }
    static constexpr int step(int index) {
        return index+1;
    }
    static constexpr bool test(int index) {
        return index < 4;
    }
    static constexpr int next(int index) {
        return index-4;
    }
};

struct Down {
    static constexpr int start {15};
    static constexpr bool end(int index) {
        return index >= 0;
    }
    static constexpr int step(int index) {
        return index-1;
    }
    static constexpr bool test(int index) {
        return index > 11;
    }
    static constexpr int next(int index) {
        return index+4;
    }
};