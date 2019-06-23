#include <iostream>
#include <random>
#include <time.h>

using namespace std;

std::default_random_engine el(time(NULL));
std::uniform_int_distribution<int> uniform_dist(0, 5); 

class GumballMachine;
class State
{
public:
    virtual void insertQuarter() = 0;
    virtual void ejectQuarter() = 0;
    virtual void turnCrank() = 0;
    virtual void dispense() = 0;
};

class NoQuarterState : public virtual State
{
private:
    GumballMachine* gumballMachine;
public:
    NoQuarterState(GumballMachine* gumballMachine) {
        this->gumballMachine = gumballMachine;
    }
    void insertQuarter() override;
    void ejectQuarter() override {
        cout << "You haven't inserted a quarter\n";
    }
    void turnCrank() override {
        cout << "You turned, but there's no quarter\n";
    }
    void dispense() override {
        cout << "You need to pay first\n";
    }
};

class HasQuarterState : public virtual State
{
private:
    GumballMachine* gumballMachine;    
public:
    HasQuarterState(GumballMachine* gumballMachine) {
        this->gumballMachine = gumballMachine;        
    }
    void insertQuarter() override {
        cout << "You can't insert another quarter\n";
    }
    void ejectQuarter() override;
    void turnCrank() override;
    void dispense() override {
        cout << "No gumball dispensed\n";
    }
};

class SoldOutState : public virtual State
{
private:
    GumballMachine* gumballMachine;
public:
    SoldOutState(GumballMachine* gumballMachine) {
        this->gumballMachine = gumballMachine;
    }
    void insertQuarter() override {
        cout << "You can't inserted a quarter, the machine is sold out\n";
    }
    void ejectQuarter() override {
        cout << "You can't eject, you haven't inserted a quarter yet\n";
    }
    void turnCrank() override {
        cout << "You turned, but there's no gumballs\n";
    }
    void dispense() override {
        cout << "No gumball dispense\n";
    }
};

class SoldState : public virtual State
{
private:
    GumballMachine* gumballMachine;
public:
    SoldState(GumballMachine* gumballMachine) {
        this->gumballMachine = gumballMachine;
    }
    void insertQuarter() override {
        cout << "Please wait, we're already giving you a gumball\n";
    }
    void ejectQuarter() override {
        cout << "Sorry, you already turned the crank\n";
    }
    void turnCrank() override {
        cout << "Turning twice doesn't get you anotherr gumball!\n";
    }
    void dispense() override;
};

class WinnerState : public virtual State
{
private:
    GumballMachine* gumballMachine;
public:
    WinnerState(GumballMachine* gumballMachine) {
        this->gumballMachine = gumballMachine;
    }
    void insertQuarter() override {
        cout << "Please wait, we're already giving you a gumball\n";
    }
    void ejectQuarter() override {
        cout << "Sorry, you already turned the crank\n";
    }
    void turnCrank() override {
        cout << "Turning twice doesn't get you anotherr gumball!\n";
    }
    void dispense() override;
};

class GumballMachine 
{
friend ostream& operator<< (ostream& out, const GumballMachine& g);
private:
    State* soldOutState;
    State* noQuarterState;
    State* hasQuarterState;
    State* soldState;
    State* winnerState;

    State* state = soldOutState;
    int count = 0;
public:
    GumballMachine(int numberGumballs) {
        soldOutState = new SoldOutState(this);
        noQuarterState = new NoQuarterState(this);
        hasQuarterState = new HasQuarterState(this);
        soldState = new SoldState(this);
        winnerState = new WinnerState(this);
        this->count = numberGumballs;
        if (numberGumballs > 0)
        {
            state = noQuarterState;
        }
    }
    
    void insertQuarter() {
        state->insertQuarter();
    }
    void ejectQuarter() {
        state->ejectQuarter();
    }
    void turnCrank() {
        state->turnCrank();
        state->dispense();
    }
    void setState(State* state) {
        this->state = state;
    }
    void releaseBall() {
        cout << "A gumball comes rolling out the slot...\n";
        if (count != 0) {
            count--;
        }
    }
    int getCount() {
        return count;
    }
    State* getNoQuarterState() {
        return noQuarterState;
    }
    State* getHasQuarterState() {
        return hasQuarterState;
    }
    State* getSoldState() {
        return soldState;
    }
    State* getSoldOutState() {
        return soldOutState;
    }
    State* getWinnerState() {
        return winnerState;
    }
};
ostream& operator<< (ostream& out, GumballMachine& g)  {
    out << "\nMighty Gumball, Inc.\n"
    << "C++-enabled Standing Gumball Model #2004\n"
    << "Inventory: " << g.getCount() << " gumballs\n";
    return out;
}

void NoQuarterState::insertQuarter() {
    cout << "You inserted a quarter\n";
    gumballMachine->setState(gumballMachine->getHasQuarterState());
}

void HasQuarterState::ejectQuarter() {
    cout << "Quarter returned\n";
    gumballMachine->setState(gumballMachine->getNoQuarterState());
}   
void HasQuarterState::turnCrank() {
    cout << "You turned...\n";
    if ((uniform_dist(el)) == 0 && (gumballMachine->getCount() > 1)) {
        gumballMachine->setState(gumballMachine->getWinnerState());
    } else {
        gumballMachine->setState(gumballMachine->getSoldState());
    }   
}

void SoldState::dispense() {
    gumballMachine->releaseBall();
    if (gumballMachine->getCount() > 0) {
        gumballMachine->setState(gumballMachine->getNoQuarterState());
    } else {
        cout << "Oops, out of gumballs!\n";
        gumballMachine->setState(gumballMachine->getSoldOutState());
    }
}

void WinnerState::dispense() {
    cout << "YOU'RE A WINNER! You get two gumballs for your quarter\n";
    gumballMachine->releaseBall();
    if (gumballMachine->getCount() == 0) {
        gumballMachine->setState(gumballMachine->getSoldOutState());
    } else {
        gumballMachine->releaseBall();
        if (gumballMachine->getCount() > 0) {
        gumballMachine->setState(gumballMachine->getNoQuarterState());
        } else {
        cout << "Oops, out of gumballs!\n";
        gumballMachine->setState(gumballMachine->getSoldOutState());
        }
    }
}

int main() {
    GumballMachine gumballMachine = GumballMachine(5);
    cout << gumballMachine << endl;
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    cout << gumballMachine << endl;
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    cout << gumballMachine << endl;
}