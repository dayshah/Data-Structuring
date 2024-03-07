
#include <iostream>
#include <string>

template<typename T>
class UniquePtr {
    private:
    T* object_ptr;

    public:
    UniquePtr(const T& object): object_ptr(new T(object)) {}
    UniquePtr(T&& other) : object_ptr(new T(std::move(other))) {}

    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;

    UniquePtr(UniquePtr&& other) noexcept: object_ptr(other.object_ptr) {
        other.object_ptr = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete this->object_ptr;
            this->object_ptr = other.object_ptr;
            other.object_ptr = nullptr;
        }
        return *this;
    }
    
    T& value() { return *object_ptr; }
    operator T() { return *object_ptr; }
    operator bool() { return object_ptr != nullptr; }
};

int main() {
    UniquePtr<std::string> up{"hello"};
    up = std::move(up);
    std::cout << up.value() << std::endl;

    return 0;
}
