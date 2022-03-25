// T2 - Beginning C++17
// Chapter 3, Pg. 77 - 80
// Chapter 11, Pg. 386

// Enumerations and Structures

#include <array>
#include <iostream>

// Exercise: Add another enumeration to Product. Similarly, extend the PRODUCT_NAMES array with the name for the new product and update the print_message function to show this new product.

// Apple Products
enum class Product
{
        IPhone,
        IPad,
        Apple_Watch,
        MacStudio,
        Count,
};

constexpr std::string_view PRODUCT_NAMES[static_cast<int>(Product::Count)] = {
        [static_cast<int>(Product::IPad)]      = "iPad",
        [static_cast<int>(Product::MacStudio)] = "Mac Studio",
        [static_cast<int>(Product::IPhone)]    = "iPhone",
        [static_cast<int>(Product::Apple_Watch)]    = "Apple_Watch",
};

constexpr auto print_message()
{
        std::printf("Select Apple Product (%d: %s, %d: %s, %d: %s): ",
                static_cast<int>(Product::IPhone),
                PRODUCT_NAMES[static_cast<int>(Product::IPhone)].data(),
                static_cast<int>(Product::IPad),
                PRODUCT_NAMES[static_cast<int>(Product::IPad)].data(),
                static_cast<int>(Product::MacStudio),
                PRODUCT_NAMES[static_cast<int>(Product::MacStudio)].data(),
                static_cast<int>(Product::Apple_Watch),
                PRODUCT_NAMES[static_cast<int>(Product::Apple_Watch)].data());
}

auto main() -> int {
        print_message();

        int opt {};
        std::cin >> opt;

        std::cout << PRODUCT_NAMES[opt] << '\n';
}