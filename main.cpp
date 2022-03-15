#include <iostream>
#include <string_view>
#include <string>


auto join(std::string a, std::string b) {return a+b;}
auto avg(float a, float b, float c){return (a+b+c)/3;}

int main()
{
        std::cout <<join("Hello", "World")<<"\n";
        std::cout<<avg(5.5,5.2,5.4)<<"\n";
}

