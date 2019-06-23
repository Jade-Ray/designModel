# include<iostream>

using namespace std;

class CaffeineBeverage
{
public:
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }
    virtual void brew() = 0;
    virtual void addCondiments() = 0;
    void boilWater() {
        cout << "Boiling water\n";
    }
    void pourInCup() {
        cout << "Pouring into cup\n";
    }
};

class Tea: public CaffeineBeverage
{
public:
    virtual void brew() override {
        cout << "Steeping the tea\n";
    }
    virtual void addCondiments() override {
        cout << "Adding Lemon\n";
    }
};

class Coffe: public CaffeineBeverage
{
public:
    virtual void brew() {
        cout << "Dripping Coffee through filter\n";
    }
    virtual void addCondiments() {
        cout << "Adding Sugar and Milk\n";
    }
};

class CaffeineBeverageWithHook
{
public:
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        if (customerWantsCondiments()) {
            addCondiments();
        }
    }
    virtual void brew() {}
    virtual void addCondiments() {}
    void boilWater() {
        cout << "Boiling water\n";
    }
    void pourInCup() {
        cout << "Pouring into cup\n";
    }
    virtual bool customerWantsCondiments() {
        return true;
    }
};

class TeaWithHook: public CaffeineBeverageWithHook
{
public:
    virtual void brew() {
        cout << "Steeping the tea\n";
    }
    virtual void addCondiments() {
        cout << "Adding Lemon\n";
    }
    bool customerWantsCondiments() {
        string answer = getUserinput();
        if ((answer == "Y") || (answer == "y")) {
            return true;
        }else
        {
            return false;
        }
    }
    string getUserinput() {
        string answer = "";
        cout << "Would you like lemon with your tea (y/n)? ";
        cin >> answer;
        if (answer.empty()) {
            return "no";
        }
        return answer;
    }
};

class CoffeWithHook: public CaffeineBeverageWithHook
{
public:
    virtual void brew() {
        cout << "Dripping Coffee through filter\n";
    }
    virtual void addCondiments() {
        cout << "Adding Sugar and Milk\n";
    }
    bool customerWantsCondiments() {
        string answer = getUserinput();
        if ((answer == "Y") || (answer == "y")) {
            return true;
        }else
        {
            return false;
        }
    }
    string getUserinput() {
        string answer = "";
        cout << "Would you like milk and sugar with your coffee (y/n)? ";
        cin >> answer;
        if (answer.empty()) {
            return "no";
        }
        return answer;
    }
};

int main() {
    Tea* myTea = new Tea();
    Coffe* myCoffe = new Coffe();
    myTea->prepareRecipe();
    myCoffe->prepareRecipe();
    cout << endl;
    TeaWithHook* tea = new TeaWithHook();
    CoffeWithHook* coffe = new CoffeWithHook();
    tea->prepareRecipe();
    coffe->prepareRecipe();
}
