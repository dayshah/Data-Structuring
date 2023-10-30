#include <iostream>

class DynamicArray {
    private:
    int* arr;
    int size;
    int capacity;

    public:
    DynamicArray(int capacity) :
        arr(new int[capacity]),
        size(0),
        capacity(capacity)
    {}

    ~DynamicArray() { delete[] arr; }

    DynamicArray(const DynamicArray& other) : 
        arr(new int[other.capacity]), 
        capacity(other.capacity),
        size(other.size)
    {
        std::copy(other.arr, other.arr+other.size, this->arr);
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            this->capacity = capacity;
            this->size = size;
            this->arr = new int[size];
            std::copy(other.arr, other.arr+other.size, this->arr);
        }
        return *this;
    }

    int& operator[](int i) { return arr[i]; }
    int get(int i) const { return arr[i]; }
    void set(int i, int n) { arr[i] = n; }

    void pushback(int n) {
        if (size == capacity) resize();
        arr[size] = n;
        ++size;
    }

    int popback() {
        --size;
        return arr[size];
    }

    void resize() {
        int* newArr = new int[capacity*2];
        std::copy(arr, arr+size, newArr);
        delete[] arr;
        arr = newArr;
        capacity *= 2;
    }

    int getSize() const { return size; }
    int getCapacity() const { return capacity; }
};

int main() {
    DynamicArray vec(3);
    vec.pushback(5);
    vec.pushback(3);
    vec.pushback(2);
    std::cout << vec.popback() << "\n";
    std::cout << vec.popback() << "\n";
    std::cout << vec.popback() << "\n";
}
