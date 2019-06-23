#include <iostream>

using namespace std;

class FlyBehavior
{
public:
    FlyBehavior(){}
    virtual void fly(){};
};

class FlyWithWings : public FlyBehavior
{
public:
    virtual void fly() {
        cout << "I'am flying!!" << endl;
    }
};

class FlyNoWay : public FlyBehavior
{
public:
    virtual void fly() {
        cout << "I can't fly" << endl;
    }
};

class FlyRocketPowered : public FlyBehavior
{
public:
    virtual void fly() {
        cout << "I'm flying with a rocket!" << endl;
    }
};


class QuackBehavior
{
public:
    QuackBehavior(){}
    virtual void quack(){};
};

class Quack : public QuackBehavior
{
public:
    virtual void quack() {
        cout << "Quack" << endl;
    }
};

class MuteQuack : public QuackBehavior
{
public:
    virtual void quack() {
        cout << "<< Silence >>" << endl;
    }
};

class Squeak : public QuackBehavior
{
public:
    virtual void quack() {
        cout << "Squeak" << endl;
    }
};


class Duck
{
private:

public:
    FlyBehavior *flyBehavior;
    QuackBehavior *quackBehavior;

    Duck() {}
    void setFlyBehavior(FlyBehavior *fb) {
        flyBehavior = fb;
    }
    void setQuackBehavior(QuackBehavior *qb){
        quackBehavior = qb;
    }
    virtual void display(){};
    void performFly() {
        flyBehavior->fly();
    }
    void performQuack() {
        quackBehavior->quack();
    }
    void swim() {
        cout << "All ducks float, even decoys!" << endl;
    }
};

class ModelDuck : public Duck
{
private:
    /* data */
public:
    ModelDuck() {
        flyBehavior = new FlyNoWay();
        quackBehavior = new Quack();
    }
    virtual void display() {
        cout << "I'm a model duck" << endl;
    }
};

int main() {
    Duck *model = new ModelDuck();
    model->display();
    model->performFly();
    model->performQuack();
    model->setFlyBehavior(new FlyRocketPowered());
    model->performFly();
    return 0;
}
