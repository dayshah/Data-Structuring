
#include <iostream>
#include <queue>
#include <thread>

template<size_t capacity>
struct RingBuffer {
    // can use
    std::array<int, capacity> array;
    int head;
    int size;
    std::mutex array_mutex;
    
    bool enQueue(int value) {
        std::lock_guard<std::mutex> lock(array_mutex);
        if (isFull()) return false;
        array[(head+size)%capacity] = value;
        ++size;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) return false;
        head = (head+1) % capacity;
        --size;
        return true;
    }
    
    int Front() {
        if (isEmpty()) return -1;
        return array[head]; 
    }
    
    int Rear() { 
        if (isEmpty()) return -1;
        return array[(head+size-1)%capacity]; 
    }
    
    bool isEmpty() { return size == 0; }
    
    bool isFull() { return size == capacity; }
};

void testFunc(int n) {std::cout << n << "\n";};

int main() {
    RingBuffer<3> rb;
    std::cout << rb.enQueue(1); // return True
    std::cout << rb.enQueue(2); // return True
    std::cout << rb.enQueue(3); // return True
    std::cout << rb.enQueue(4); // return False
    std::cout << rb.Rear();     // return 3
    std::cout << rb.isFull();   // return True
    std::cout << rb.deQueue();  // return True
    std::cout << rb.enQueue(4); // return True
    std::cout << rb.Rear();     // return 4
    std::thread t1(testFunc, 100);
    std::thread t3(&RingBuffer<3>::deQueue, &rb);
    std::thread t2(&RingBuffer<3>::enQueue, &rb, 2);
    t1.join();
    t3.join();
    t2.join();
    
    std::cout << rb.Rear();
}
