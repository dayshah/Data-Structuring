
#include <iostream>
#include <span>
#include <array>
#include <vector>

template<typename T>
void printAll(T arg) {
    std::cout << arg << '\n';
}

template<typename T, typename... Ts>
void printAll(T arg, Ts... args) {
    //auto func = [](auto arg) { std::cout << arg << '\n'; };
    std::cout << sizeof...(Ts) << '\n';
    std::cout << arg << '\n';
    printAll(args...);
    //func<Ts>(args)...;
}

template<typename... Ts>
void printAll2(Ts... args) {
    std::initializer_list<int>{(std::cout << args << '\n', 0)...};   
}
template<typename... Ts>
void printAll3(Ts... args) {
    (std::cout << ... << args) << '\n';   
}

template<int Num>
consteval int factorial() {
    if constexpr (Num <= 1) {
        return 1;
    } else {
        return Num * factorial<Num-1>();
    }
}

void takeSpan(const std::span<int> spanner) {
    std::cout << spanner[0];
}

int main() {
    //printAll(1, 2.0, "hello", 3);
    printAll2(1, 2.0, "hello", 3);
    constexpr int result = factorial<5>();
    std::cout << result << '\n';
    std::vector<int> testing{1,2,3};
    takeSpan(testing);
    return 0;
}
