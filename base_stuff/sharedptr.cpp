#include <iostream>
#include <ostream>

struct InPlaceConstruct{};

template <typename T>
class SharedPtr {
    private:
    T* object_ptr;
    int* count_ptr;

    public:
    // Create from T
    SharedPtr(const T& object)
        : object_ptr(new T(object)), count_ptr(new int(1))
    { }

    SharedPtr(T&& object) noexcept
        : object_ptr(new T(std::move(object))), count_ptr(new int(1))
    { }

    template<typename... Args>
    SharedPtr(InPlaceConstruct, Args&&... args):
        object_ptr(new T(std::forward<Args>(args)...)), count_ptr(new int(1))
    { std::cout << "in place constructing" << std::endl; }

    // Rule of 5
    SharedPtr(const SharedPtr& other) noexcept
        : object_ptr(other.object_ptr), count_ptr(other.count_ptr)
    {
        ++(*count_ptr);
    }
    SharedPtr& operator=(const SharedPtr& other) noexcept
    {
        if (this != &other) {
            --(*count_ptr);
            if (*count_ptr == 0 ) {
                delete object_ptr;
                delete count_ptr;
                std::cout << "destroying underlying" << std::endl;
            }
            object_ptr = other.object_ptr;
            count_ptr = other.count_ptr;
            ++(*count_ptr);
        }
        return *this;
    }
    SharedPtr(SharedPtr&& other) noexcept
        : object_ptr(other.object_ptr), count_ptr(other.count_ptr) {}
    SharedPtr& operator=(SharedPtr&& other)
    {
        if (this != &other) {
            object_ptr = other.object_ptr;
            count_ptr = other.count_ptr;
            (*count_ptr) += 1;
        }
        return *this;
    }
    ~SharedPtr()
    {
        --(*count_ptr);
        if (*count_ptr == 0) { 
            delete object_ptr;
            delete count_ptr;
            std::cout << "destroying underlying" << std::endl;
        }
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
        std::cout << stinky2->howBad << std::endl;
    }
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
