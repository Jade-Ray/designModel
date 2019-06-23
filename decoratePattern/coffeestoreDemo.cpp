# include <iostream>

using namespace std;

class Beverage
{
public:
    string description = "Unknow Beverage";
    
    virtual string getDescription() {
        return description;
    }
    virtual double cost(){}
};

class CondimentDecorator : public Beverage
{
public:
    virtual string getDescription(){}
};

class Espresso : public Beverage
{
public:
    Espresso() {
        description = "Espresso";
    }
    virtual double cost() {
        return 1.99;
    }
};

class HouseBlend : public Beverage
{
public:
    HouseBlend() {
        description = "House Blend Coffee";
    }
    virtual double cost() {
        return .89;
    }
};

class Mocha : public CondimentDecorator
{
public:
    Beverage *beverage;

    Mocha(Beverage *beverage) {
        this->beverage = beverage;
    }
    virtual string getDescription() {
        return beverage->getDescription() + ", Mocha";
    }
    virtual double cost() {
        return .20 + beverage->cost();
    }
};

class Soy : public CondimentDecorator
{
public:
    Beverage *beverage;

    Soy(Beverage *beverage) {
        this->beverage = beverage;
    }
    virtual string getDescription() {
        return beverage->getDescription() + ", Soy";
    }
    virtual double cost() {
        return .15 + beverage->cost();
    }
};

class Whip : public CondimentDecorator
{
public:
    Beverage *beverage;

    Whip(Beverage *beverage) {
        this->beverage = beverage;
    }
    virtual string getDescription() {
        return beverage->getDescription() + ", Whip";
    }
    virtual double cost() {
        return .10 + beverage->cost();
    }
};

int main() {
    Beverage *beverage = new Espresso();
    beverage = new Mocha(beverage);
    beverage = new Mocha(beverage);
    beverage = new Soy(beverage);
    cout << beverage->getDescription() << " $" << beverage->cost() << endl;
}