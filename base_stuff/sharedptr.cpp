#include <atomic>
#include <iterator>
#include <memory>
#include <iostream>
#include <ostream>
#include <string>
#include <string_view>

template <typename T>
class SharedPtr {
    private:
    T* object_ptr;
    std::atomic_int* count_ptr;

    public:
    SharedPtr<T>(const T& object)
    {
        this->object_ptr = new T(object);
        this->count_ptr = new std::atomic_int(1);
        std::cout << "constructing new shared ptr from copied object" << std::endl;
    }
    SharedPtr<T>(T&& object)
    {
        this->object_ptr = new T(std::move(object));
        this->count_ptr = new std::atomic_int(1);
        std::cout << "constructing new shared ptr from moved obj" << std::endl;
    }
    SharedPtr<T>(const SharedPtr<T>& sharedPtr)
        : object_ptr(sharedPtr.object_ptr), count_ptr(sharedPtr.count_ptr)
    {
        (*count_ptr)++;
        std::cout << "copy constructed sharedPtr from sharedPtr" << std::endl;
    }
    ~SharedPtr<T>()
    {
        (*count_ptr)--;
        if (*count_ptr == 0) delete object_ptr;
        std::cout << "shared ptr destructor called count: " << *count_ptr << std::endl;
    }

    int getCount() const {
        return *count_ptr;
    }
    operator bool() const {
        return object_ptr != nullptr;
    }

    const T& operator*() const {
        return *object_ptr;
    }
    T& operator*() {
        return *object_ptr;
    }

    T* operator->() {
        return object_ptr;
    }
    const T* operator->() const {
        return object_ptr;
    }
};

struct StinkyIsBad {
    int howBad;
    StinkyIsBad(int howBad) {
        this->howBad = howBad;
        std::cout << "constructing stink" << std::endl;
    }
    StinkyIsBad(const StinkyIsBad& copy): howBad(copy.howBad) {
       std::cout << "copy constructing stink" << std::endl;
    }
    StinkyIsBad(StinkyIsBad&& mover) noexcept: howBad(mover.howBad) {
        std::cout << "move constructing stink (doesn't matter)" << std::endl;
    }
    ~StinkyIsBad() {
        std::cout << "stinky destructor called" << std::endl;
    }

    void increaseBad() { ++howBad; }

    friend std::ostream& operator<<(std::ostream& os, const StinkyIsBad& obj) {
        os << obj.howBad;
        return os;
    }
};

int main() {
    StinkyIsBad hello(0);
    StinkyIsBad& helloRef(hello);
    SharedPtr<StinkyIsBad> test(helloRef);
    std::cout << std::endl;

    SharedPtr<StinkyIsBad> my_sp(StinkyIsBad(2));
    SharedPtr<StinkyIsBad> sp2 = my_sp;
    SharedPtr<StinkyIsBad> sp3(sp2);
    my_sp->increaseBad();
    if (my_sp)
        std::cout << *my_sp << std::endl;
    sp2->increaseBad();
    std::cout << *sp3 << std::endl;
    return 0;
}
