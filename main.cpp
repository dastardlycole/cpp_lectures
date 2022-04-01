
#include <vector>
#include <iostream>
#include <algorithm>

// Products
enum class Product
{
        Invalid=-1,
        Cereal,
        Shampoo,
        Vegetables,
        Shoes,
        Fruits,
        Count,
};
struct Item
{
        std::string name;
        Product type;
        float price;
        int units;
        std::string best_before;

};
struct Inventory
{
        std::vector<Item> my_items;

        auto add_item(Item const& item)
        {    
                my_items.push_back(item);
                return true;}
                
        auto remove_item(Item const& item)        
        {       
                auto pos = find(my_items.begin(),my_items.end(),item);
                my_items.erase(my_items.begin()+pos);
                return true;
        }

        auto find_item()
};
