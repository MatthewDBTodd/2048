#ifndef MOVEFACTORY_H
#define MOVEFACTORY_H

#include <map>
#include <memory>
#include "Mover.h"

using ptr = std::shared_ptr<Mover>;

class MoveFactory {
private:
    std::map<char, ptr> movers;
public:
    MoveFactory();
    ptr get(const char ch); 
};

#endif