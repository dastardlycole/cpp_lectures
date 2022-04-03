
#include <vector>
#include <iostream>
#include <algorithm>

constexpr auto MAX_ITEMS      = 30;
constexpr auto MAX_MODEL_NAME = 64; 
 

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

/// @brief Holds the names of the product categories.
constexpr std::string_view PRODUCT_NAMES[static_cast<int>(Product::Count)] = {
    [static_cast<int>(Product::Cereal)]       = "Cereal",
    [static_cast<int>(Product::Shampoo)]      = "Shampoo",
    [static_cast<int>(Product::Vegetables)]   = "Vegetables",
    [static_cast<int>(Product::Shoes)]        = "Shoes",
    [static_cast<int>(Product::Fruits)]       = "Fruits",
};

/// @brief Checks if the given product is valid.
constexpr auto is_valid_product(Product prod) { return prod > Product::Invalid && prod < Product::Count; }

/// @brief Return the name of the given product.
constexpr auto get_product_name(Product prod)
{
        if (!is_valid_product(prod)) { return std::string_view {""}; }

        return PRODUCT_NAMES[static_cast<int>(prod)];
}

/// @brief Prints a list of all the product categories available.
auto list_products()
{
        std::cout << "Product list: \n";
        std::for_each_n(std::begin(PRODUCT_NAMES), std::size(PRODUCT_NAMES), [i = 0](const auto& name) mutable {
                std::printf("(%d) %s\n", i, name.data());
                i++;
        });
        std::printf("---------------\n");
}

/// Represents a stocked item corresponding to one of the listed product categories.

struct Item
{
        std::string name;
        Product type;
        float price;
        int units;
        std::string best_before;

        Item() = default;

        Item(const Product prod, const std::string& name, const float price, const int units, const std::string& best_before) :
                type {prod}, name {name}, price {price}, units {units}, best_before {best_before}
        {}

        auto print() const { std::printf("%32s%64s%16.2f%8d\n", get_product_name(type).data(), name.c_str(), price, units); }
};


struct Inventory
{
        using SearchPredicate = std::function<bool(const Item&)>;
        using Items           = std::vector<Item>;
        using ItemPtr         = Items::iterator;   
        
        std::vector<Item> my_items;
       
        auto add_item(Item const& item)
        {    
                my_items.push_back(item);    
                return true;}
                
        auto remove_item(ItemPtr item)        
        {       
                // auto pos = std::find(my_items.begin(),my_items.end(),item);
                // if (pos==my_items.end())
                // {
                //         return false;
                // }
                my_items.erase(item);
                return true;
        }
        // reference chat for find_item
        auto find_item(SearchPredicate const& pred)
        {
                auto pitem = std::find_if(my_items.begin(),my_items.end(),pred);
                if (pitem != my_items.end()) 
                { 
                        return pitem; 
                }

                return ItemPtr {};
        }
        
        auto find_free_space()
        {
                int size=0;
                for(auto i:my_items)
                {
                      size+=i.units;  
                }
                int free_space=30-size;
                return free_space;
        }

        /// @brief Prints a table listing currently stocked items in the inventory.
        auto list()
        {
                std::printf("%32s%64s%16s%8s\n", "Product", "Model Name", "Price (GBP)", "Qty.");
                std::for_each(my_items.begin(), my_items.end(), [](const auto& item) { item.print(); });
                std::printf("---------------\n");
        }
        
};

struct User
{
        std::string username;
        std::string password;
        Inventory inventory;

        User() = default;

        User(const std::string& username, const std::string& password,const Inventory& inventory) :
                username {username}, password {password}, inventory {inventory}
        {}
};
User loggedinuser;
struct User_db
{
        using Users = std::vector<User>;
        std::vector<User> my_users; 

        auto add_user(User const& user)
        {    
                my_users.push_back(user);    
                return true;}
                      
};
auto get_logged(User_db const& user_db)
{
        
}

struct InventoryUI
{
        enum class Option
        {
                Invalid      = -1,
                AddItem      = 'a',
                RemoveItem   = 'r',
                EditItem     = 'e',
                SearchItem   = 's',
                ListProducts = 'p',
                ListItems    = 'l',
                Quit         = 'q',
        };

        Inventory inventory;
        loggedinuser.inventory=inventory;

        auto      list_options()
        {       std::cout<<"Inventory size is: "<<30-inventory.find_free_space()<<"/30\n";
                std::printf("(%c) Add Item\n", static_cast<char>(Option::AddItem));
                std::printf("(%c) Search Item and view/remove/edit\n", static_cast<char>(Option::SearchItem));
                std::printf("(%c) List Product Categories\n", static_cast<char>(Option::ListProducts));
                std::printf("(%c) List Items in Stock\n", static_cast<char>(Option::ListItems));
                std::printf("(%c) Quit\n", static_cast<char>(Option::Quit));
        }

        auto get_user_action()
        {
                char opt {};
                std::printf("Select operation: ");
                std::scanf(" %c", &opt);
                std::printf("---------------\n");
                return opt;
        }

        /// @brief Adds item to the inventory.
        auto handle_add_option()
        {
                Item item;
                do {
                        list_products();

                        std::printf("Select product category to add: ");
                        int pid {};
                        std::scanf("%d", &item.type);

                        if (!is_valid_product(item.type)) { std::printf("Invalid option selected. Please try again.\n"); }
                        else
                        {
                                // NOTE(CA, 28.03.2022) - Important to note that we need to consume the whitespaces from user input when using getline
                                std::printf("Enter model name: ");
                                std::getline(std::cin >> std::ws, item.name);

                                std::printf("Enter price: ");
                                std::cin >> item.price;

                                std::printf("Enter quantity: ");
                                std::cin >> item.units;

                                return item;
                        }

                } while (true);
        }
        
        /// @brief Search item by name or product category to perform remove or edit operations on the found item.
        auto handle_search_option()
        {
                char opt {};
                std::printf("Search by (n) Name, (t) Product Type, (p) Product price: ");
                std::cin >> opt;

                Inventory::ItemPtr pitem;

                if (opt == 'n')
                {
                        // search for item by name
                        std::string name {};
                        std::printf("Enter model name: ");
                        std::getline(std::cin >> std::ws, name);
                        pitem = inventory.find_item([&](const Item& item) { return item.name == name; });


                        if (pitem != Inventory::ItemPtr {}){
                                // we ask the user what they'd like to do with this found item
                                        do {    
                                                pitem->print();
                                                std::printf("---------------\n");

                                                std::printf("(%c) Remove Item\n", static_cast<char>(Option::RemoveItem));
                                                std::printf("(%c) Edit Item\n", static_cast<char>(Option::EditItem));
                                                std::printf("(%c) Quit\n", static_cast<char>(Option::Quit));
                                                const auto opt = get_user_action();

                                                if (opt == static_cast<char>(Option::RemoveItem))
                                                {
                                                        inventory.remove_item(pitem);
                                                        std::cout<<"Inventory size is: "<<30-inventory.find_free_space()<<"\n";
                                                        break;
                                                }

                                                if (opt == static_cast<char>(Option::EditItem))
                                                {
                                                        // NOTE(CA, 28.03.2022) - This is cumbersome to use and also inefficient. You should swap in-place or
                                                        // just edit a property of interest but that'd be more complicated.
                                                        const auto new_item = handle_add_option();
                                                        inventory.remove_item(pitem);
                                                        inventory.add_item(new_item);
                                                        break;
                                                }

                                                if (opt == static_cast<char>(Option::Quit)) { break; }

                                                std::printf("Invalid option selected. Please try again.\n");
                                                
                                        } while (true);
                        }
                        else { std::printf("Item not found. Try adding an item.\n"); }

                }
                else if (opt == 't')
                {
                        // search for item by product type
                        Product prod {Product::Invalid};
                        list_products();
                        std::printf("Select product id: ");
                        std::scanf("%d", &prod);
                        std::printf("Selected product category: %s\n", get_product_name(prod).data());

                        std::printf("%32s%64s%16s%8s\n", "Product", "Model Name", "Price (GBP)", "Qty.");
                        for (auto the_item:inventory.my_items)
                        {
                                if(the_item.type == prod)
                                {the_item.print(); };
                        }
                        std::printf("---------------\n");

                        do{
                                
                                std::printf("---------------\n");
                                std::printf("(%c) Quit\n", static_cast<char>(Option::Quit));
                                const auto opt = get_user_action();
                                if (opt == static_cast<char>(Option::Quit)) { break; }

                                std::printf("Invalid option selected. Please try again.\n");
                        }while(true);        


                        
                        
                }
                else if (opt == 'p')
                {
                        // search for item by product type
                        float my_price;
                        std::printf("Select product price: ");
                        std::scanf("%f", &my_price);
                        std::printf("Here are products that cost %f: \n", my_price);

                        std::printf("%32s%64s%16s%8s\n", "Product", "Model Name", "Price (GBP)", "Qty.");
                        for (auto the_item:inventory.my_items)
                        {
                                if(the_item.price == my_price)
                                {the_item.print(); };
                        }
                        std::printf("---------------\n");

                        do{
                                
                                std::printf("---------------\n");
                                std::printf("(%c) Quit\n", static_cast<char>(Option::Quit));
                                const auto opt = get_user_action();
                                if (opt == static_cast<char>(Option::Quit)) { break; }

                                std::printf("Invalid option selected. Please try again.\n");
                        }while(true);        


                        
                        
                }
                else
                {
                        std::printf("Invalid option selected. Please try again.\n");
                        return;
                }

                
                        }
        
        auto run()
        {
                
                

                do {
                        list_options();
                        const auto opt = get_user_action();
                        if (opt == static_cast<char>(Option::AddItem))
                        {
                                const auto item = handle_add_option();
                                
                                inventory.add_item(item);
                                if (inventory.find_free_space()<=0)
                                {Inventory::ItemPtr pitem = inventory.find_item([&](const Item& the_item) { return the_item.name == item.name; });
                                        inventory.remove_item(pitem);
                                        std::cout<<"Unable to add item. Inventory has "<<inventory.find_free_space()<<"units of space left.\n\n";}
                                else
                                {std::printf("Added item\n\n");
                                std::cout<<"Inventory size is: "<<30-inventory.find_free_space()<<"\n";}
                                
                        }
                        else if (opt == static_cast<char>(Option::SearchItem)) { handle_search_option(); }
                        else if (opt == static_cast<char>(Option::ListProducts)) { list_products(); }
                        else if (opt == static_cast<char>(Option::ListItems)) { inventory.list(); }
                        else if (opt == static_cast<char>(Option::Quit)) { break; }
                        else { std::printf("Invalid option selected. Please try again.\n"); }
                } while (true);
        }
};



auto main() -> int
{      
        User_db the_User_db;
        std::printf("Shop Inventory v0.1\n");
        std::string first_op {};
        std::printf("1 to signup. 2 to login \n");
        std::getline(std::cin >> std::ws, first_op);

        if(first_op=="1")
        {
        std::string cust_name {};
        std::printf("What is your name/business' name? \n");
        std::getline(std::cin >> std::ws, cust_name);
        std::string cust_password {};
        std::printf("What is your password? \n");
        std::getline(std::cin >> std::ws, cust_password);
        User user;
        user.username=cust_name;
        user.password=cust_password;
        the_User_db.add_user(user);}

        else if(first_op=="1")
        {
        std::string cust_name {};
        std::printf("What is your name/business' name? \n");
        std::getline(std::cin >> std::ws, cust_name);
        std::string cust_password {};
        std::printf("What is your password? \n");
        std::getline(std::cin >> std::ws, cust_password);

        for (auto one : the_User_db.my_users)
        {
                if (one.username==cust_name &&one.password==cust_password)
                {
                        loggedinuser=one;
                        
                }
                
        }




        InventoryUI ui {};

        ui.run();
}