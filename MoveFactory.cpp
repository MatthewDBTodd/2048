
#include "MoveFactory.h"
using ptr = std::shared_ptr<Mover>;

MoveFactory::MoveFactory() {
    ptr u {new Up()};
    ptr d {new Down()};
    ptr r {new Right()};
    ptr l {new Left()};
    movers.insert({'u', u});
    movers.insert({'d', d});
    movers.insert({'r', r});
    movers.insert({'l', l});
}

ptr MoveFactory::get(const char ch) {
    auto it {movers.find(ch)};
    if (it == movers.end()) {
        throw std::exception();
    }
    return movers[ch];
}