#include <iostream>
#include <mutex>
#include <thread>
#include <functional>

class Singleton {
    private:
    int data;

    inline static Singleton* instance{nullptr};
    inline static std::mutex inst_mutex{};
    
    Singleton(): data(0) 
    {}

    public:
    Singleton(Singleton& other) = delete;
    Singleton& operator=(Singleton& other) = delete;

    static Singleton& getSingleton() {
        if (instance == nullptr) {
            std::scoped_lock lock{inst_mutex};
            if (instance == nullptr)
                instance = new Singleton{};
        }
        return *instance;
    }

    int getData() const { return data; }
};

int main() {
    std::cout << "start" << std::endl;

    std::function<void(std::string_view)> func = [](std::string_view str) {
        std::cout << str << Singleton::getSingleton().getData() << std::endl;
    };

    std::thread thread1{func, "1 "};
    std::thread thread2{func, "2 "};

    std::cout << Singleton::getSingleton().getData() << std::endl;
    
    thread1.join();
    thread2.join();
    return 0;
}
