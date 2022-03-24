#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// The Sky is blue -> [The, Sky, is, blue]
// TheSkyBlue

using Words = std::vector<std::string>;

auto extract_words(Words& words, std::string text, std::string_view separators)
{
        auto   start = text.find_first_not_of(separators);
        size_t end {};

        while (start != std::string::npos)
        {
                end = text.find_first_of(separators, start + 1);
                if (end == std::string_view::npos) { end = text.length(); }
                std::string s {text.substr(start, end - start)};
                words.push_back(s);
                start = text.find_first_not_of(separators, end + 1);
        }
}
auto isOdd(int i)
        {
               
                if (i % 2 == 0)
                        {return false;}
                else
                        {return true;}
              
        }
auto main() -> int
{
        // std::cout << "Enter some text: ";
        // std::string input {};
        // std::getline(std::cin, input);
        // Words words {};
        // extract_words(words, input, " \t");

        // std::for_each(words.begin(), words.end(), [](auto& w) { std::cout << w << '\n'; });

        std::vector<int>numbers {};
        std::cout << "Enter a list of integers(0 to terminate): ";
        std::string input {};
        std::getline(std::cin,input);
        

                

        for (char i:input)
        {       
                int x = i - '0';  
                if(x==0)
                {
                        break;
                }
                if(i !=' ')
                {
                        numbers.push_back(x);
                }
                
        }
        std::for_each(numbers.begin(), numbers.end(), [](auto& w) { std::cout << w << '\n'; });
        int noOdd = count_if(numbers.begin(), numbers.end(),isOdd);
        std::cout << "Total no of odd numbers is: "<< noOdd<<"\n";
        

}