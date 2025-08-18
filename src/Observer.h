#ifndef OBSERVER_H
#define OBSERVER_H

#include "GameObject.h"

class GameObject;

class Observer{
    public:
    virtual void update(const GameObject& obj)=0;
};

#endif