#include <algorithm>          // std::remove
#include <iostream>           // std::cin
#include <string>             // std::string
#include <string_view>        // std::string_view

int main()
{
        // Copy, Substring, Find, Join
        std::string date {};
        std::cout << "Enter the date: ";
        std::getline(std::cin, date);
        std::cout<<"Date: "<<date<<"\n";

        std::string date_copy {};
        date_copy+=date;
        std::cout<<"Copy of Date: "<<date_copy<<"\n";

        // std::string date_copy(date.size(),'\0');
        // std::copy(date.begin(),date.end(),date_copy.begin());


        std::string third_date {'m','y',' ','b','i','r','t','h','d','a','y',' ','i','s',':',' ',' ',};
        std::copy(date.begin(),date.end(),third_date.end());
        std::cout<<"Random + Date: "<<third_date<<"\n";




}