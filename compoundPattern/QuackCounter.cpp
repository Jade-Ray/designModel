# pragma once
#include "QuackableInterface.cpp"

class QuackCounter : public virtual QuackableInterface
{
private:
    QuackableInterface* duck;
    static int numberOfQuacks;
public:
    QuackCounter(QuackableInterface* duck){
        this->duck = duck;
    }
    void quack() override {
        duck->quack();
        numberOfQuacks++;
    }
    void registerObserver(Observer* observer) override {
        duck->registerObserver(observer);
    }
    void notifyObservers() override {
        duck->notifyObservers();
    }
    static int getQuacks();
};

int QuackCounter::numberOfQuacks = 0;

int QuackCounter::getQuacks() {
    return numberOfQuacks;
}