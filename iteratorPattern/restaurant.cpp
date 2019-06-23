#include <iostream>
#include <vector>

using namespace std;

class MenuItem
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
    string getName() {
        return name;
    }
    string getDescription() {
        return description;
    }
    bool getVegetarian() {
        return vegetarian;
    }
    double getPrice() {
        return price;
    }
};

class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual MenuItem* Next()  = 0;
};

class PancakeHouseMenuIterator: public Iterator {
private:
    vector<MenuItem*> items;
    int postion = 0;
public:
    PancakeHouseMenuIterator(vector<MenuItem*> items) {
        this->items = items;
    }
    virtual bool hasNext() override {
        if ((postion >= items.size()) || (items[postion] == NULL)) {
            return false;
        }else
        {
            return true;
        }      
    }
    virtual MenuItem* Next() override {
        MenuItem* mennuItem = items[postion];
        postion ++;
        return mennuItem;
    }
};

class DinerMenuIterator: public Iterator {
private:
    MenuItem* items;
    int postion = 0;
public:
    DinerMenuIterator(MenuItem* items) {
        this->items = items;
    }
    virtual bool hasNext() override {
        if ((postion >= sizeof items) || (items[postion].getName().empty())) {
            return false;
        }else
        {
            return true;
        }      
    }
    virtual MenuItem* Next() override {
        MenuItem* mennuItem = &items[postion];
        postion ++;
        return mennuItem;
    }
};

class Menu {
public:
    virtual Iterator* createIterator() = 0;
};

class PancakeHouseMenu : public virtual Menu
{
private:
    vector<MenuItem*> menuItems;
public:
    PancakeHouseMenu() {
        addItem("K&B's Pancake Breakfast", "Pancakess with scrambled eggs, and toast", true, 2.99);
        addItem("Regular Pancake Breakfast", "Pancakess with fried eggs, and toast", false, 2.99);
        addItem("Blueberry Pancake", "Pancakess made with freash blueberries", true, 3.49);
        addItem("Walffles", "Waffles, with your choice of blueberries or strawberries", true, 3.59);
    }
    void addItem(string name, string description, bool vegetarian, double price) {
        MenuItem* menuItem = new MenuItem(name, description, vegetarian, price);
        menuItems.push_back(menuItem);
    }
    Iterator* createIterator() override {
        return new PancakeHouseMenuIterator(menuItems);
    }
};

class DinerMenu : public Menu
{
private:
    static const int MAX_ITEMS = 6;
    int numberOfItems = 0;
    MenuItem* menuItems;

public:
    DinerMenu() {
        menuItems = new MenuItem[MAX_ITEMS];
        addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on wholes wheat)", true, 2.99);
        addItem("BLI", "Bacon with lettuce & tomatoo on whole wheat", false, 2.99);
        addItem("Soup of the day", "Soup of the day, with a side side of potato salad", false, 3.29);
        addItem("Hotdog", "A hot dog, with saurkrant, relish, onions, topped with cheese", false, 3.05);
    }
    void addItem(string name, string description, bool vegetarian, double price) {
        MenuItem menuItem(name, description, vegetarian, price);
        if (numberOfItems >= MAX_ITEMS) {
            cout << "Sorry, menu id full! Can't add item to menu\n";
        }else {
            menuItems[numberOfItems] = menuItem;
            numberOfItems++;
        }
    }
    Iterator* createIterator() override {
        return new DinerMenuIterator(menuItems);
    }
};

class Waitress {
private:
    Menu* pancakeHouseMenu;
    Menu* dinerMenu;
    void printMenu(Iterator* iterator) {
        while (iterator->hasNext())
        {
            MenuItem* menuItem = iterator->Next();
            cout << menuItem->getName() << ", "
            << menuItem->getPrice() << " -- "
            << menuItem->getDescription() << endl;
        }
    }
public:
    Waitress(Menu* pancakeHouseMenu, Menu* dinerMenu) {
        this->pancakeHouseMenu = pancakeHouseMenu;
        this->dinerMenu = dinerMenu;
    }
    void printMenu() {
        Iterator* pancakeIterator = pancakeHouseMenu->createIterator();
        Iterator* dinerIterator = dinerMenu->createIterator();
        cout << "MENU\n----\nBREAKFAST\n";
        printMenu(pancakeIterator);
        cout << "\nLUNCH\n";
        printMenu(dinerIterator);
    }
};

int main() {
    PancakeHouseMenu* pancakeHouseMenu = new PancakeHouseMenu();
    DinerMenu* dinerMenu = new DinerMenu();

    Waitress* waitress = new Waitress(pancakeHouseMenu, dinerMenu);

    waitress->printMenu();
}