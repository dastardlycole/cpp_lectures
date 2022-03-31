
#include <array>
#include <iostream>

// Products
enum class Product
{
        Invalid=-1,
        Cereal,
        Shampoo,
        Vegetables,
        Shoes,
        Count,
};
struct Item
{
        std::string name;
        Product type;
        float price;

};
