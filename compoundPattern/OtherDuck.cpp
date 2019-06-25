# pragma once
#include "QuackableInterface.cpp"

class DuckCall : public virtual QuackableInterface
{
private:
    Observerable* observerable;
public:
    DuckCall() {
        this->observerable = new Observerable(this);
    }
    void quack() override {
        cout << "Kwak\n";
        notifyObservers();
    }
    void registerObserver(Observer* observer) override {
        observerable->registerObserver(observer);
    }
    void notifyObservers() override {
        observerable->notifyObservers();
    }
};

class RubberDuck : public virtual QuackableInterface
{
private:
    Observerable* observerable;
public:
    RubberDuck() {
        this->observerable = new Observerable(this);
    }
    void quack() override {
        cout << "Squeak\n";
        notifyObservers();
    }
    void registerObserver(Observer* observer) override {
        observerable->registerObserver(observer);
    }
    void notifyObservers() override {
        observerable->notifyObservers();
    }
};