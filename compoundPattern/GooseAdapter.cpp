# pragma once
#include "QuackableInterface.cpp"

class Goose 
{
public:
    void honk() {
        cout << "Honk\n";
    }
};

class GooseAdapter : public virtual QuackableInterface 
{
private:
    Goose* goose;
    Observerable* observerable;
public:
    GooseAdapter(Goose* goose){
        this->goose = goose;
        this->observerable = new Observerable(this);
    }
    void quack() override {
        goose->honk();
        notifyObservers();
    }
    void registerObserver(Observer* observer) override {
        observerable->registerObserver(observer);
    }
    void notifyObservers() override {
        observerable->notifyObservers();
    }
};