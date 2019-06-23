#include <iostream>

using namespace std;

class Duck
{
public:
    virtual void quack() {}
    virtual void fly() {}
};

class MallardDuck : public Duck
{
public:
    virtual void quack() {
        cout << "Quack\n";
    }
    virtual void fly() {
        cout << "I'am flying\n";
    }
};

class Turkey
{
public:
    virtual void gobble() {}
    virtual void specificFly() {}
};

class WildTurkey: public Turkey
{
public:
    virtual void gobble() {
        cout << "Gobble gobble\n";
    }
    virtual void specificFly() {
        cout << "I'am flying a short distance\n";
    }    
};

class TurkeyAdapter : public Duck, public WildTurkey
{
public:
    virtual void quack() {
        this->gobble();
    }
    virtual void fly() {
        for (int i=0; i<5; i++) {
            this->specificFly();
        }
    }
};

void testDuck(Duck* duck) {
    duck->quack();
    duck->fly();
};

int main() {
    MallardDuck* duck = new MallardDuck();
    WildTurkey* turkey = new WildTurkey();
    Duck* turkeyAdapter = new TurkeyAdapter();

    cout << "The Turkey says...\n";
    turkey->gobble();
    turkey->specificFly();

    cout << "\nThe Duck says...\n";
    testDuck(duck);

    cout << "\nThe TurkeyAdapter says...\n";
    testDuck(turkeyAdapter);
}