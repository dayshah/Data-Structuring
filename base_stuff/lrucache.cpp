
#include <unordered_map>
#include <list>
#include <optional>
#include <iostream>

struct LRUCache {
    std::unordered_map<int, int> cache;
    std::unordered_map<int, std::list<int>::iterator> eraseMap;
    std::list<int> keysUsedOrder;
    int capacity;

    LRUCache(int capacity): capacity(capacity) {
        cache.reserve(capacity);
        eraseMap.reserve(capacity);
    }

    int get(int key) {
        auto found = cache.find(key);
        if (found == cache.end()) return -1;
        keysUsedOrder.erase(eraseMap[key]);
        eraseMap[key] = keysUsedOrder.insert(keysUsedOrder.end(), key);
        return found->second;
    }

    void put(int key, int value) {
        if (get(key) != -1) {
            cache[key] = value;
        } else {
            if (cache.size() == capacity) {
                int keyToRemove = keysUsedOrder.front();
                cache.erase(keyToRemove);
                eraseMap.erase(keyToRemove);
                keysUsedOrder.pop_front();
            }
            cache[key] = value;
            eraseMap[key] = keysUsedOrder.insert(keysUsedOrder.end(), key);
        }
    }
};

int main() {
    LRUCache cache(4);
    cache.put(3, 2);
    //std::cout << cache.get(3).value_or(-1) << '\n';
    cache.put(3,1);
    cache.put(10, 3);
    std::cout << cache.keysUsedOrder.back() << '\n';
    cache.get(3);
    std::cout << cache.keysUsedOrder.back() << '\n';
    cache.get(10);
    std::cout << cache.keysUsedOrder.back() << '\n';
    return 0;
}

