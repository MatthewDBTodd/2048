#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
public:
    virtual void draw(const Board& b, const int score, const int turns) const = 0;
};

class TerminalDisplay : public Display {
private:
    static constexpr int tileWidth {15};
    static constexpr int tileHeight {7};
    static constexpr int horizontalMargin {6};
    static constexpr int numColours {6};
    static const char* verticalPadding;
    std::string setWidth(std::string val) const;
    void displayTile(std::string val) const;
public:
    virtual void draw(const Board& b, const int score, const int turns) const override;
};

#endif