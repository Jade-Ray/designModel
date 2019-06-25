#pragma once

#include <vector>
#include "Observer.cpp"

class QuackObservable
{
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

class Observerable : public virtual QuackObservable
{
private:
    std::vector<Observer*> observers;
    QuackObservable* duck;
public:
    Observerable(QuackObservable* duck);
    void registerObserver(Observer* observer) override;
    void notifyObservers() override;
};

Observerable::Observerable(QuackObservable *duck)
{
    this->duck = duck;
}
void Observerable::registerObserver(Observer *observer)
{
    observers.push_back(observer);
}
void Observerable::notifyObservers()
{
    for (auto observer : observers)
    {
        observer->update(duck);
    }
}