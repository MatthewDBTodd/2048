#ifndef MERGELISTENER_H
#define MERGELISTENER_H

class MergeListener {
public:
    virtual void notify(const int value) = 0;
};

#endif