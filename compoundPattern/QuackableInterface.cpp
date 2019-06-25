#pragma once
#include <iostream>
#include "QuackObservable.cpp"

using namespace std;

class QuackableInterface : public virtual QuackObservable
{
private:
    /* data */
public:
    QuackableInterface(/* args */);
    ~QuackableInterface();
    virtual void quack() = 0;
};

QuackableInterface::QuackableInterface(/* args */)
{
}

QuackableInterface::~QuackableInterface()
{
}
