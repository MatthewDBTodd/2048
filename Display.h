#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>

class Display {
public:
    virtual void draw(const Board& b) const = 0;
};

class TerminalDisplay : public Display {
public:
    virtual void draw(const Board& b) const override;
};

#endif