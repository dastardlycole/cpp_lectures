#include <array>           // std::array
#include <iostream>        // std::cout, std::cin, std::scanf
#include <cmath>        // std::cout, std::cin, std::scanf
#include <utility>         // std::pair

constexpr auto NUM_FUNCTIONS = 7;

auto           ask_user_continue() -> bool
{
        std::cout << "Would you like to continue (y/n): ";
        char opt {};
        std::cin >> opt;
        return opt != 'n';
}

auto ask_user_arithemtic() -> int
{
        std::cout << "Press 'a' for addition." << '\n';
        std::cout << "Press 's' for subtraction." << '\n';
        std::cout << "Press 'm' for multiplication." << '\n';
        std::cout << "Press 'd' for division." << '\n';
        std::cout << "Press 'r' for remainder." << '\n';
        std::cout << "Press 'p' for power." << '\n';

        char opt {};
        std::cin >> opt;
        switch (opt)
        {
                case 'a': return 1;
                case 's': return 2;
                case 'm': return 3;
                case 'd': return 4;
                case 'r': return 5;
                case 'p': return 6;
                default: return 0;
        }
}

auto ask_user_numbers() -> std::pair<float, float>
{
        std::cout << "Enter two numbers (x y): ";
        float x {}, y {};
        std::scanf("%f %f", &x, &y);
        return std::make_pair(x, y);
}

// Task 1 -> Implement the power and remainder operations.
// Task 2 -> Declare the `res` variable.
// Task 3 -> Create an array containing functions that perform arithmetic. (Hint: See example)

// Keyword: Function Signature -> ReturnType (Parameters...)
using BinaryFn = float (*)(float, float);

constexpr auto                                nop(float x, float y) -> float { return 0; }

constexpr auto                                add(float x, float y) -> float { return x + y; }
constexpr auto                                subtract(float x, float y) -> float { return x - y; }
constexpr auto                                multiply(float x, float y) -> float { return x * y; }
constexpr auto                                divide(float x, float y) -> float { return x / y; }
constexpr auto                                rem(float x, float y) -> float { return fmod(x,y); }
constexpr auto                                power(float x, float y) -> float { return pow(x,y); }

constexpr std::array<BinaryFn, NUM_FUNCTIONS> FN {nop, add, subtract, multiply, divide, rem, power};

auto                                          main() -> int
{
        std::cout << "Calculator v0.3" << '\n';
        float res {};

        char opt {};
        do {
                const auto op     = ask_user_arithemtic();
                const auto [a, b] = ask_user_numbers();
                switch (op)
                {
                        case 1: res = add(a, b);
                        break;
                        case 2: res = subtract(a, b);
                        break;
                        case 3: res = multiply(a, b);
                        break;
                        case 4: res = divide(a, b);
                        break;
                        case 5: res = rem(a, b);
                        break;
                        case 6:res = power(a, b);
                        break;
                        default: std::cout << "Unknown operation selected. Please select again." << '\n'; continue;
                }
                std::cout << "Result: " << res << '\n';
                if (!ask_user_continue()) { break; }
        } while (true);
}