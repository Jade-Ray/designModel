# pragma once
#include "QuackableInterface.cpp"

class MallardDuck : public virtual QuackableInterface
{
private:
    Observerable* observerable;
public:
    MallardDuck() {
        observerable = new Observerable(this);
    }
    void quack() override {
        cout << "Quack\n";
        notifyObservers();
    }
    void registerObserver(Observer* observer) override {
        observerable->registerObserver(observer);
    }
    void notifyObservers() override {
        observerable->notifyObservers();
    }
};
