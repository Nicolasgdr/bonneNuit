#ifndef OBSERVABLE_H
#define OBSERVABLE_H
#include "Observer.h"
class Observable{
public:
    virtual void registerObserver(Observer *)=0;
    virtual void notifyObserver(Observable*)=0;
};
#endif // OBSERVABLE_H
