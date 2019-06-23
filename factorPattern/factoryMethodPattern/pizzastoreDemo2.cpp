# include <iostream>
# include <vector>

using namespace std;

class Pizza
{
public:
    string name;
    string dough;
    string sauce;
    vector<string> toppings;

    void prepare() {
        cout << "Preparing " << name << endl
        << "Tossing dough...\n" << "Adding sauce...\n"
        << "Adding toppings: " << endl;
        for (auto topping : toppings) {
            cout << "\t" << topping << endl;
        }
    }
    void bake() {
        cout << "Bake for 25 minutes at 350\n";
    }
    virtual void cut() {
        cout << "Cutting the pizza into diagonal slices\n";
    }
    void box() {
        cout << "Place pizza in official PizzaStore box\n";
    }
    string getName() {
        return name;
    }
};

class NYStyleCheese : public Pizza
{
public:
    NYStyleCheese() {
        name = "NY Style Sauce and Cheese Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";
        toppings.push_back("Grated Reggiano Cheese");
    }
};

class ChicageStyleCheese : public Pizza
{
public:
    ChicageStyleCheese() {
        name = "Chicago Style Deep Dish Cheese Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";
        toppings.push_back("shredded Mozzarella Cheese");
    }
    void cut() {
        cout << "Cutting the pizza into square slices\n";
    }
};

class PizzaStore
{
public:
    Pizza *orderPizza(string type) {
        Pizza *pizza;
        pizza = createPizza(type);
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();
        return pizza;
    }
    virtual Pizza *createPizza(string type) {return NULL;}
};

class NYPizzaStore : public PizzaStore
{
public: 
    virtual Pizza *createPizza(string type) {
        if (type == "cheese") {
            return new NYStyleCheese();
        } else {
            return NULL;
        }
    }
};

class ChicagePizzaStore : public PizzaStore
{
public: 
    virtual Pizza *createPizza(string type) {
        if (type == "cheese") {
            return new ChicageStyleCheese();
        } else {
            return NULL;
        }
    }
};

int main() {
    PizzaStore *nyStore = new NYPizzaStore();
    PizzaStore *chicageStoe = new ChicagePizzaStore();

    Pizza *pizza = nyStore->orderPizza("cheese");
    cout << "Ethan ordered a " << pizza->getName() << endl;
    cout << endl;
    pizza = chicageStoe->orderPizza("cheese");
    cout << "Joel ordered a " << pizza->getName() << endl;
}