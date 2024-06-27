#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Item {
public:
    string name;
    double price;
    int stock;

    Item(string n, double p, int s) : name(n), price(p), stock(s) {}
};

class Store ()
private:
    vector<Item> inventory;
    vector<Item> cart;
    double totalPrice;

public:
    Store() : totalPrice(0) {}

    void addItemToInventory() {
        string name;
        double price;
        int stock;
        cout << "Enter item name: ";
        cin >> name;
        cout << "Enter item price: ";
        cin >> price;
        cout << "Enter item stock: ";
        cin >> stock;
        inventory.push_back(Item(name, price, stock));
        cout << "Item added to inventory.\n";
    }

    void listInventory() {
        cout << "Inventory:\n";
        for (size_t i = 0; i < inventory.size(); ++i) {
            cout << i + 1 << ". " << inventory[i].name << " - " << inventory[i].price << " - " << inventory[i].stock << " in stock\n";
        }
    }