
#include <unordered_map>
#include <iostream>





int main() {
    std::unordered_map<int, int> hello;
    std::cout << hello[1] << "\n";
    int* arr(new int[10]);
    arr[1] = 1;
    std::cout << arr[1] << "\n";
}

