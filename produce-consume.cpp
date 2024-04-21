#include <iostream>
#include <mutex>
#include <ostream>  
#include <queue>
#include <thread>
#include <condition_variable>
#include <functional>

// You have a consumer and producer. 
// The producer produce strings, then adds them to a shared buffer.
// The consumer takes these strings out of the shared buffer, and prints them with '*' characters surrounding them.
// The producer and consumer must run on different threads. Shared buffer access must be synchronized to avoid data races.
// The queue should have a max length. 
// The producer should wait until there is an available spot in the queue before adding anything to the shared structure. 
// The consumer should wait until there is at least 1 string in the queue before doing anything. 
// Model this problem in C++ using classes and std lib primitives.

template <typename T, size_t MaxSize>
class CircularQueue {
    private:
    std::array<T, MaxSize> queue;
    size_t start;
    size_t size;

    size_t getBackIndex() {
        return start+size >= MaxSize
            ? (start + size) - MaxSize
            : start+size;
    }

    public:
    CircularQueue(): queue{}, start{0}, size{0} {};

    size_t getSize() { return size; }

    bool push_back(T&& item) {
        if (size >= MaxSize)
            return false;
        queue[getBackIndex()] = std::forward<T>(item);
        ++size;
        return true;
    }

    T pop_front() {
        T popped = std::move(queue[start]);
        if (++start >= MaxSize) start = 0;
        --size;
        return popped;
    }
};

template <size_t MaxSize>
class SharedBuffer {
    private:
    CircularQueue<std::string, MaxSize> queue;
    std::mutex qMutex;
    std::condition_variable cvToAdd;
    std::condition_variable cvToGet;

    public:
    SharedBuffer(): queue{}, qMutex{}, cvToAdd{}, cvToGet{} {}

    void addString(std::string&& word) {
        std::unique_lock<std::mutex> locker{qMutex};
        cvToAdd.wait(locker, [this]() { return queue.getSize() < MaxSize; });

        std::cout << "Produced: " << word << std::endl;
        queue.push_back(std::move(word));

        locker.unlock();
        cvToGet.notify_one();
    }

    void getString() {
        std::unique_lock<std::mutex> locker{qMutex};
        cvToGet.wait(locker, [this]() { return queue.getSize() > 0; });

        std::cout << "*" << queue.pop_front() << "*" << std::endl;

        locker.unlock();
        cvToAdd.notify_one();
    }
};

template <size_t BufferSize>
struct Producer {
    void operator()(SharedBuffer<BufferSize>& buffer, std::vector<std::string>& words) {
        for (auto& word : words) {
            buffer.addString(std::move(word));
        }
    }
};

template <size_t BufferSize, int NumOfWords>
struct Consumer {
    void operator()(SharedBuffer<BufferSize>& buffer) {
        for (int i = 0; i < NumOfWords; ++i) {
            buffer.getString();
        }
    }
};

int main() {
    std::vector<std::string> words{};
    constexpr int NUM_OF_WORDS = 100;
    for (int i = 0; i < NUM_OF_WORDS; ++i) {
        words.push_back("hello" + std::to_string(i));
    }

    constexpr int BUFFER_SIZE = 10;
    SharedBuffer<BUFFER_SIZE> buffer{};

    std::jthread producerThread{Producer<BUFFER_SIZE>{}, std::ref(buffer), std::ref(words)};
    std::jthread consumerThread(Consumer<BUFFER_SIZE, NUM_OF_WORDS>{}, std::ref(buffer));

    return 0;
}