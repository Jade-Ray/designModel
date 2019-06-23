# include <iostream>
# include <vector>

using namespace std;

class Dough
{};
class ThinCrustDough : public Dough
{};

class Sauce
{};
class MarinaraSauce : public Sauce
{};
class PlumTomatoSauce : public Sauce
{};

class Cheese
{};
class ReggianoCheese : public Cheese
{};
class MozzarellaCheese : public Cheese
{};

class PizzaIngredientFactory
{
public:
    virtual Dough *createDough() {}
    virtual Sauce *createSauce() {}
    virtual Cheese *createCheese() {}
};

class NYPizzaIngradientFactory : public PizzaIngredientFactory
{
public:
    Dough *createDough() {
        return new ThinCrustDough();
    }
    Sauce *createSauce() {
        return new MarinaraSauce();
    }
    Cheese *createCheese() {
        return new ReggianoCheese();
    }
};

class ChicagoPizzaIngradientFactory : public PizzaIngredientFactory
{
public:
    Dough *createDough() {
        return new ThinCrustDough();
    }
    Sauce *createSauce() {
        return new PlumTomatoSauce();
    }
    Cheese *createCheese() {
        return new MozzarellaCheese();
    }
};

class Pizza
{
public:
    string name;
    Dough *dough;
    Sauce *sauce;
    Cheese *cheese;

    virtual void prepare() {}
    void bake() {
        cout << "Bake for 25 minutes at 350\n";
    }
    virtual void cut() {
        cout << "Cutting the pizza into diagonal slices\n";
    }
    void box() {
        cout << "Place pizza in official PizzaStore box\n";
    }
    void setName(string name) {
        this->name = name;
    }
    string getName() {
        return name;
    }
};

class CheesePizza : public Pizza
{
public:
    PizzaIngredientFactory *ingredientFactory;
    CheesePizza(PizzaIngredientFactory *ingredientFactory) {
        this->ingredientFactory = ingredientFactory;
    }
    void prepare() {
        cout << "Preparing " << name << endl;
        dough = ingredientFactory->createDough();
        cout << "Tossing dough...\n";
        sauce = ingredientFactory->createSauce();
        cout << "Adding sauce...\n";
        cheese = ingredientFactory->createCheese();
        cout << "Adding toppings: \n";
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
        Pizza *pizza = NULL;
        PizzaIngredientFactory *ingredientFactory = new NYPizzaIngradientFactory();
        if (type == "cheese") {
            pizza = new CheesePizza(ingredientFactory);
            pizza->setName("New York Style Cheese Pizza");
        }
        return pizza;
    }
};

class ChicagePizzaStore : public PizzaStore
{
public: 
    virtual Pizza *createPizza(string type) {
        Pizza *pizza = NULL;
        PizzaIngredientFactory *ingredientFactory = new ChicagoPizzaIngradientFactory();
        if (type == "cheese") {
            pizza = new CheesePizza(ingredientFactory);
            pizza->setName("Chicago Style Cheese Pizza");
        }
        return pizza;
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