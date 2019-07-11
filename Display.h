#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>

class Display {
public:
    virtual void draw(const Board& b) const = 0;
    virtual void gameOver(const Board& b) const = 0;
};

class TerminalDisplay : public Display {
public:
    virtual void draw(const Board& b) const override;
    virtual void gameOver(const Board& b) const override;
private:
    static constexpr int tileWidth {15};
    static constexpr int tileHeight {7};
    static constexpr int horizontalMargin {6};
    static constexpr int numColours {6};
    static constexpr int size {16};
    std::string prepareString(std::string val) const;
    void displayBoard(const Board& b) const;
    void displayTile(std::string val) const;
};

#endif