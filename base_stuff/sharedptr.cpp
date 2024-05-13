#include <iostream>
#include <ostream>
#include <atomic>

struct InPlaceConstruct{};

template <typename T>
class SharedPtr {
    private:
    T* object_ptr;
    std::atomic<int>* counter;
    void cleanup() {
        if (counter && counter->fetch_sub(1, std::memory_order_acq_rel) - 1 == 0) { 
            delete object_ptr;
            delete counter;
            std::cout << "destroying underlying" << std::endl;
        }
    }
    public:
    // Create from T
    SharedPtr(const T& object)
        : object_ptr(new T(object)), counter{new std::atomic<int>{1}}
    {}

    SharedPtr(T&& object) noexcept
        : object_ptr(new T(std::move(object))), counter{new std::atomic<int>{1}}
    {}

    template<typename... Args>
    SharedPtr(InPlaceConstruct, Args&&... args)
        : object_ptr(new T(std::forward<Args>(args)...)), counter{new std::atomic<int>{1}}
    {}

    // Rule of 5
    SharedPtr(const SharedPtr& other) noexcept
        : object_ptr(other.object_ptr),
        counter(other.counter)
    {
        counter->fetch_add(1, std::memory_order_relaxed);
    }
    SharedPtr& operator=(const SharedPtr& other) noexcept {
        if (this != &other) {
            cleanup();
            object_ptr = other.object_ptr;
            counter = other.counter;
            counter->fetch_add(1, std::memory_order_relaxed);
        }
        return *this;
    }

    SharedPtr(SharedPtr&& other) noexcept
        : object_ptr(other.object_ptr), counter(other.counter) 
    {
        other.object_ptr = nullptr;
        other.counter = nullptr;
    }
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            cleanup();
            object_ptr = other.object_ptr;
            counter = other.counter;
            other.object_ptr = nullptr;
            other.counter = nullptr;
        }
        return *this;
    }

    ~SharedPtr() {
        cleanup();
    }

    int getCount() const {
        return counter->load();
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
    int howGood;
    StinkyIsBad(int howBad, int howGood) {
        this->howBad = howBad;
        this->howGood = howGood;
    }
    void increaseBad() { ++howBad; }
    friend std::ostream& operator<<(std::ostream& os, const StinkyIsBad& obj) {
        os << obj.howBad;
        return os;
    }
};

int main() {
    SharedPtr<StinkyIsBad> stinky1 = SharedPtr<StinkyIsBad>{InPlaceConstruct{}, 1, 2};
    {
        SharedPtr<StinkyIsBad> stinky2{{2,1}};
        stinky1 = stinky2;
        stinky2 = stinky2;
        std::cout << stinky2.getCount() << std::endl;
    }
    std::cout << stinky1.getCount() << '\n';
    SharedPtr<StinkyIsBad> stinky3 = stinky1;
    stinky1->increaseBad();
    //std::cout << stinky1->howBad << std::endl;

    // SharedPtr<StinkyIsBad> my_sp(StinkyIsBad(2));
    // SharedPtr<StinkyIsBad> sp2 = my_sp;
    // SharedPtr<StinkyIsBad> sp3(sp2);
    // my_sp->increaseBad();
    // if (my_sp)
    //     std::cout << *my_sp << std::endl;
    // sp2->increaseBad();
    // std::cout << *sp3 << std::endl;
    return 0;
}
