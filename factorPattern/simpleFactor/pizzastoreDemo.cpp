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
    void cut() {
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

class SimplePizzaFactory 
{
public:
    Pizza *createPizza(string type) {
        Pizza *pizza = NULL;
        if (type == "cheese") {
            pizza = new NYStyleCheese();
        }
        return pizza;
    }
};

class PizzaStore
{
public:
    SimplePizzaFactory *factory;

    PizzaStore(SimplePizzaFactory *factory) {
        this->factory = factory;
    }
    Pizza *orderPizza(string type) {
        Pizza *pizza;
        pizza = factory->createPizza(type);
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();
        return pizza;
    }
};

int main() {
    SimplePizzaFactory* factor = new SimplePizzaFactory();
    PizzaStore *pizzaStore = new PizzaStore(factor);
    Pizza *pizza = pizzaStore->orderPizza("cheese");
    cout << "Ethan ordered a " << pizza->getName() << endl;
}