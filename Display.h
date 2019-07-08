#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
public:
    virtual void draw(const Board& b, const int score, const int turns) const = 0;
};

class TerminalDisplay : public Display {
private:
    static constexpr int tileWidth {11};
    static constexpr int tileHeight {3};
    static const char* verticalPadding;
    std::string setWidth(std::string val) const;
    void initColours() const;
    void displayColourTile(int colorVal, std::string val) const;
    void displayZeroTile() const;
public:
    virtual void draw(const Board& b, const int score, const int turns) const override;
};

#endif