# pragma once
# include <iostream>
#include "QuackableInterface.cpp"
#include "MallardDuck.cpp"
#include "RedheadDuck.cpp"
#include "OtherDuck.cpp"
#include "QuackCounter.cpp"

class AbstractDuckFactory
{
public:
    virtual QuackableInterface* createMallardDuck() = 0;
    virtual QuackableInterface* createRedheadDuck() = 0;
    virtual QuackableInterface* createDuckCall() = 0;
    virtual QuackableInterface* createRubberDuck() = 0;
};

class DuckFactory : public virtual AbstractDuckFactory
{
public:
    QuackableInterface* createMallardDuck() override {
        return new MallardDuck();
    }
    QuackableInterface* createRedheadDuck() override {
        return new RedheadDuck();
    }
    QuackableInterface* createDuckCall() override {
        return new DuckCall();
    }
    QuackableInterface* createRubberDuck() override {
        return new RubberDuck();
    }
};

class CountingDuckFactory : public virtual AbstractDuckFactory
{
public:
    QuackableInterface* createMallardDuck() override {
        return new QuackCounter(new MallardDuck());
    }
    QuackableInterface* createRedheadDuck() override {
        return new QuackCounter(new RedheadDuck());
    }
    QuackableInterface* createDuckCall() override {
        return new QuackCounter(new DuckCall());
    }
    QuackableInterface* createRubberDuck() override {
        return new QuackCounter(new RubberDuck());
    }
};