# pragma once
#include "QuackableInterface.cpp"

class RedheadDuck : public virtual QuackableInterface
{
private:
    Observerable* observerable;
public:
    RedheadDuck() {
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
