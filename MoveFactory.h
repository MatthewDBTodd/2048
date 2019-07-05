#ifndef MOVEFACTORY_H
#define MOVEFACTORY_H

#include <map>
#include <memory>
#include "Mover.h"

class MoveFactory {
    using ptr = std::shared_ptr<Mover>;
private:
    std::map<char, ptr> movers;
public:
    MoveFactory() {
        ptr u {new Up()};
        ptr d {new Down()};
        ptr r {new Right()};
        ptr l {new Left()};
        movers.insert({'u', u});
        movers.insert({'d', d});
        movers.insert({'r', r});
        movers.insert({'l', l});
    }
    ptr get(char ch) {
        return movers[ch];
    }
};

#endif