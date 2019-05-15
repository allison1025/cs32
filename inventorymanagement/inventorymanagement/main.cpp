//=======================================================================================
// Name        : Assign2_CS2B.cpp
// Author      : Zade Lobo
// Date        : Fall 2017
// Version     : 1.0.3
// Copyright   : Copyright (C). CS Department Foothill College 2017. All rights reserved.
// Description : Simulation of an inventory manager for an electronics store using text
//               files, arrays of pointers, dynamic memory allocation, inheritance, and
//               static casting with C++
// Revision History:
//      October 28, 2017: Base code written
//      October 30, 2017: Implementations defined and called
//      October 31, 2017: Debugging (ran for the first time)
//      November 1, 2017: Formatting corrected
//=======================================================================================

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
using namespace std;


int generateProductID ()
{
    int id = 0;
    id = rand() % 10000;
    return id;
}

class InventoryItem
{
public:
    InventoryItem();
    InventoryItem(string name, int quantity);
    ~InventoryItem();
    void set_item_name(string name);
    void set_item_quantity(int quantity);
    string get_item_name() const;
    int get_item_quantity() const;
    void Display() const;
protected:
    string item_name_;
    int item_quantity_;
};

InventoryItem::InventoryItem()
{
    item_quantity_ = 0;
}

InventoryItem::InventoryItem(string name, int quantity)
{
    item_name_ = name;
    item_quantity_ = quantity;
}

void InventoryItem::Display() const
{
    cout << "Name: " << item_name_ << endl;
    cout << "Quantity: " << item_quantity_ << endl;
}

string InventoryItem::get_item_name() const
{
    return item_name_;
}

int InventoryItem::get_item_quantity() const
{
    return item_quantity_;
}

InventoryItem::~InventoryItem()
{
    cout << "InventoryItem " << item_name_ << " with " << item_quantity_ << " items destroyed..." << endl;
}

class Product: public InventoryItem
{
public:
    Product();
    Product(string name, int quantity, double price, string condition);
    void set_product_id();
    void set_product_price(double price);
    void set_product_condition(string condition);
    int get_product_id() const;
    double get_product_price() const;
    string get_product_condition() const;
    void DisplayProduct() const;
    ~Product();
private:
    int product_id_;
    double product_price_;
    string product_condition_;
};

Product::Product()
{
    product_id_ = 0;
    product_price_ = 0.0;
}

Product::Product(string name, int quantity, double price, string condition)
{
    item_name_ = name;
    item_quantity_ = quantity;
    product_price_ = price;
    product_condition_ = condition;
    product_id_ = generateProductID();
}

void Product::set_product_id()
{
    product_id_ = generateProductID();
}

void Product::set_product_price(double price)
{
    product_price_ = price;
}

void Product::set_product_condition(string condition)
{
    product_condition_ = condition;
}

int Product::get_product_id() const
{
    return product_id_;
}

double Product::get_product_price() const
{
    return product_price_;
}

string Product::get_product_condition() const
{
    return product_condition_;
}

void Product::DisplayProduct() const
{
    Display();
    cout << "Product #" << product_id_ << endl;
    cout << "Price: " << setprecision(2) << fixed << product_price_ << endl;
    cout << "Condition: ";
    if (product_condition_ == "D")
    {
        cout << "Defective" << endl;
    }
    if (product_condition_ == "U")
    {
        cout << "Used" << endl;
    }
    if (product_condition_ == "R")
    {
        cout << "Refurbished" << endl;
    }
    if (product_condition_ == "N")
    {
        cout << "New" << endl;
    }
    cout << "************************************" << endl;
}

class InventorySystem
{
public:
    InventorySystem();
    InventorySystem(string store_name, int store_id);
    void BuildInventory();
    void ShowInventory() const;
    void ShowDefectInventory() const;
    void Terminate() const;
    void set_store_name(string name);
    void set_store_id(int id);
    void set_item_count(int count);
    string get_store_name() const;
    int get_store_id() const;
    int get_item_count() const;
    ~InventorySystem();
private:
    string store_name_;
    int store_id_;
    InventoryItem* items_[512];
    int item_count_;
};

InventorySystem::InventorySystem()
{
    store_name_ = "";
    store_id_ = 0;
    item_count_ = 0;
    for (int i=0; i< 512; i++)
    {
        items_[i] = NULL;
    }
    srand(time(NULL));
}

InventorySystem::InventorySystem(string store_name, int store_id)
{
    store_name_ = store_name;
    store_id_ = store_id;
    item_count_ = 0;
    for (int i=0; i< 512; i++)
    {
        items_[i] = NULL;
    }
    srand(time(NULL));
}

void InventorySystem::BuildInventory()
{
    ifstream file ("inventory.txt");
    InventoryItem* i = NULL;
    Product* p = NULL;
    string name;
    int quantity=0;
    double price=0.0;
    string condition;
    string buffer;
    if (!file)
    {
        cout << "ERROR: Failed to open input file\n";
        exit(-1);
    }
    while (getline(file, buffer, ';') )
    {
        name = buffer;
        getline(file, buffer, ';');
        quantity= atol(buffer.c_str());
        getline (file, buffer, ';') ;
        price = atof(buffer.c_str());
        getline (file, buffer, '\n') ;
        condition = buffer.c_str();
        i = new Product(name, quantity, price, condition);
        p = static_cast <Product*>(i);
        p->set_product_condition(condition);
        p->set_product_id();
        p->set_product_price(price);
        items_[item_count_] = p;
        ++item_count_;
    }
}

void InventorySystem::ShowInventory() const
{
    cout << "Inventory at " << store_name_ << " Auto-Generated Report:" << endl;
    cout << "**********************************************" << endl;
    for (int i = 0; i<item_count_; ++i)
    {
        Product* p = static_cast <Product*>(items_[i]);
        p->DisplayProduct();
    }
}

void InventorySystem::ShowDefectInventory() const
{
    cout << endl << endl << "Here is the defect inventory: " << endl;
    cout << "**********************************************" << endl;
    for (int i = 0; i<item_count_; ++i)
    {
        Product* p = static_cast <Product*>(items_[i]);
        if (p->get_product_condition() == "D")
        {
            p->DisplayProduct();
        }
    }
}

void InventorySystem::Terminate() const
{
    ofstream myfile ("end.txt");
    if (myfile.is_open())
    {
        for (int i=0; i<item_count_; ++i) // write "backwards"
        {
            Product* p = static_cast <Product*>(items_[i]);
            myfile << p->get_item_name() << ";" << p->get_item_quantity() << ";" << p->get_product_price() << ";" << p->get_product_condition()<< endl;
        }
    }
    else
    {
        throw("Unable to write to file");
    }
}

InventorySystem::~InventorySystem()
{
    for (int i=0; i < 512; i++)
    {
        delete items_[i];
    }
}

int main() {
    InventorySystem* p_system = NULL;
    p_system = new InventorySystem("Best Buy", 7328);
    p_system->BuildInventory();
    p_system->ShowInventory();
    p_system->ShowDefectInventory();
    p_system->Terminate();
    delete p_system;
    exit(0);
}

