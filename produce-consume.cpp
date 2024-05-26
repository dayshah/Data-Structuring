#include <iostream>
#include <mutex>
#include <ostream>  
#include <queue>
#include <thread>
#include <condition_variable>
#include <functional>

template<size_t Size>
concept SizeMoreThanZero = Size > 0;

template <typename T, size_t MaxSize> requires SizeMoreThanZero<MaxSize>
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
    static_assert(MaxSize > 0);
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
    std::condition_variable cv;

    public:
    SharedBuffer(): queue{}, qMutex{}, cv{} {}

    void addString(std::string&& word) {
        std::unique_lock<std::mutex> locker{qMutex};
        cv.wait(locker, [this]() { return queue.getSize() < MaxSize; });

        std::cout << word << std::endl;
        queue.push_back(std::move(word));

        cv.notify_one();
        locker.unlock();
    }

    void getString() {
        std::unique_lock<std::mutex> locker{qMutex};
        cv.wait(locker, [this]() { return queue.getSize() > 0; });

        std::cout << "*" << queue.pop_front() << "*" << std::endl;

        cv.notify_one();
        locker.unlock();
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
    constexpr int NUM_OF_WORDS = 1000;
    for (int i = 0; i < NUM_OF_WORDS; ++i) {
        words.push_back("hello" + std::to_string(i));
    }

    constexpr int BUFFER_SIZE = 0;
    SharedBuffer<BUFFER_SIZE> buffer{};

    std::jthread producerThread{Producer<BUFFER_SIZE>{}, std::ref(buffer), std::ref(words)};
    std::jthread consumerThread(Consumer<BUFFER_SIZE, NUM_OF_WORDS>{}, std::ref(buffer));

    return 0;
}
