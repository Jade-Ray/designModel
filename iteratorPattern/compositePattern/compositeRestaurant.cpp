#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class MenuComponent
{
public:
    virtual void add(MenuComponent* menuComponent) = 0;
    virtual void remove(MenuComponent* menuComponent) = 0;
    virtual MenuComponent* getChild(int i) = 0;
    virtual string getName() = 0;
    virtual string getDescription() = 0;
    virtual double getPrice() = 0;
    virtual bool isVegetarian() = 0;
    virtual void print() = 0;
};

class MenuItem : public virtual MenuComponent
{
private:
    string name;
    string description;
    bool vegetarian;
    double price;

public:
    MenuItem() {}
    MenuItem(string name, string description, bool vegetarian, double price) {
        this->name = name;
        this->description = description;
        this->vegetarian = vegetarian;
        this->price = price;
    }
    virtual void add(MenuComponent* menuComponent) {}
    virtual void remove(MenuComponent* menuComponent) {}
    virtual MenuComponent* getChild(int i) { return NULL; }
    string getName() override {
        return name;
    }
    string getDescription() override {
        return description;
    }
    bool isVegetarian() override {
        return vegetarian;
    }
    double getPrice() override {
        return price;
    }
    void print() override {
        cout << "\t" << getName();
        if (isVegetarian()) {
            cout << "(v)";
        }
        cout << ", " << getPrice() << endl
        << "\t--" << getDescription() << endl;
    }
};

class Menu : public virtual MenuComponent
{
private:
    vector<MenuComponent*> menuComponents;
    string name;
    string description;
public:
    Menu (string name, string description) {
        this->name = name;
        this->description = description;
    }
    virtual void add(MenuComponent* menuComponent) override {
        menuComponents.push_back(menuComponent);
    }
    virtual void remove(MenuComponent* menuComponent) override {
        if (find(menuComponents.begin(), menuComponents.end(), menuComponent) != menuComponents.end()) {
            menuComponents.erase(find(menuComponents.begin(), menuComponents.end(), menuComponent));
        }     
    }
    virtual MenuComponent* getChild(int i) override {
        return menuComponents[i];
    }
    virtual string getName() override {
        return name;
    }
    virtual string getDescription() override {
        return description;
    }
    virtual double getPrice() { return 0; }
    virtual bool isVegetarian() { return false; }
    virtual void print() override {
        cout << "\n" << getName() << ", " << getDescription()
        << endl << "--------------------------" << endl;
        for (auto menuComponent : menuComponents) {
            menuComponent->print();
        }
    }
};

class Waitress
{
private:
    MenuComponent* allMenus;
public:
    Waitress (MenuComponent* allMenues) {
        this->allMenus = allMenues;
    }
    void printMenu() {
        allMenus->print();
    }
};

int main() {
    MenuComponent* pancakeHouseMenu = new Menu("PANCAKE HOUSE MENU", "Breakfast");
    MenuComponent* dinerMenu = new Menu("DINNER MENU", "Lunch");
    MenuComponent* cafeMenu = new Menu("CAFE MENU", "Dinner");
    MenuComponent* dessertMenu = new Menu("DESSERT MENU", "Dessert of course!");

    MenuComponent* allMenus = new Menu("ALL MENUS", "All menus combined");
    allMenus->add(pancakeHouseMenu);
    allMenus->add(dinerMenu);
    allMenus->add(cafeMenu);

    pancakeHouseMenu->add(new MenuItem("K&B's Pancake Breakfast", "Pancakess with scrambled eggs, and toast", true, 2.99));
    pancakeHouseMenu->add(new MenuItem("Regular Pancake Breakfast", "Pancakess with fried eggs, and toast", false, 2.99));
    pancakeHouseMenu->add(new MenuItem("Blueberry Pancake", "Pancakess made with freash blueberries", true, 3.49));
    pancakeHouseMenu->add(new MenuItem("Walffles", "Waffles, with your choice of blueberries or strawberries", true, 3.59));
    dinerMenu->add(new MenuItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on wholes wheat)", true, 2.99));
    dinerMenu->add(new MenuItem("BLI", "Bacon with lettuce & tomatoo on whole wheat", false, 2.99));
    dinerMenu->add(new MenuItem("Soup of the day", "Soup of the day, with a side side of potato salad", false, 3.29));
    dinerMenu->add(new MenuItem("Hotdog", "A hot dog, with saurkrant, relish, onions, topped with cheese", false, 3.05));
    dinerMenu->add(dessertMenu);
    cafeMenu->add(new MenuItem("Veggie Burger and Air Fries", "Veggie burger on a whole wheat buh, lettuce, tomato, and fries", true, 3.99));
    cafeMenu->add(new MenuItem("Soup of the day", "A cup of soup of the day, whit a side salad", false, 3.69));
    cafeMenu->add(new MenuItem("Burrito", "A large burrito, whit whole pinto beans, salsa, guacamole", true, 4.29));
    dessertMenu->add(new MenuItem("Pie", "Apple pie with a flakey crust, topped with vanilla ice cream", true, 1.59));
    dessertMenu->add(new MenuItem("Cheesecake", "Creamy New York cheesecake, with a chocolate graham crust", true, 1.99));
    dessertMenu->add(new MenuItem("Sorbet", "A scoop of raspberry and scoop of lime", true, 1.59));

    Waitress* waitress = new Waitress(allMenus);
    waitress->printMenu();
}