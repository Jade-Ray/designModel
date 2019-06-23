#include <iostream>

using namespace std;

class ChocolateBoiler
{
private:
    bool empty;
    bool boiled;
    ChocolateBoiler() {
        empty = true;
        boiled = false;
    }

public:
    static ChocolateBoiler& getInstance() {
        static ChocolateBoiler uniqueInstance;
        return uniqueInstance;
    }
    void fill() {
        if (isEmpty()) {
            empty = false;
            boiled = false;
            cout << "锅炉内填满巧克力和牛奶的混合物" << endl;
        }
    }
    void drain() {
        if (!isEmpty() && isBoiled()) {
            empty = true;
            cout << "排出煮沸的巧克力和牛奶" << endl;
        }
    }
    void boil() {
        if (!isEmpty() && !isBoiled()) {
            boiled = true;
            cout << "将炉内物煮沸" << endl;
        }
    }
    bool isEmpty() {
        return empty;
    }
    bool isBoiled() {
        return boiled;
    }
};

int main() {
    ChocolateBoiler chocolateBoiler = ChocolateBoiler::getInstance();
    chocolateBoiler.fill();
    chocolateBoiler.boil();
    chocolateBoiler.drain();
}