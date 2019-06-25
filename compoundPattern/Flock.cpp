# pragma once
#include "QuackableInterface.cpp"
#include <vector>

class Flock : public virtual QuackableInterface
{
private:
    std::vector<QuackableInterface*> ducks;
public:
    void add(QuackableInterface* duck) {
        ducks.push_back(duck);
    }
    void quack() override {
        for (auto duck : ducks) {
            duck->quack();
        }
    }
    void registerObserver(Observer* observer) override {
        for (auto duck : ducks) {
            duck->registerObserver(observer);
        }    
    }
    void notifyObservers() override {}
};