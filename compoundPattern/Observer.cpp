#pragma once
#include <typeinfo>
#include "QuackObservable.cpp"

class QuackObservable;

class Observer
{
public:
    virtual void update(QuackObservable* duck) = 0;
};

class Quackologist : public virtual Observer
{
public:
    void update(QuackObservable* duck) override;
};

void Quackologist::update(QuackObservable* duck){
    std::cout << "Quackologist: just quacked.\n";
}