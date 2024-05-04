#include <iostream>
#include <unordered_map>
#include <unordered_set>

struct LFUCache {

    // holds key->(frequency, value)
    std::unordered_map<int, std::pair<int,int>> cache;
    //holds frequency->(set of keys)
    std::unordered_map<int, std::unordered_set<int>> frequencies;
    //SHOULD BE INT -> LRU CACHE FOR TIES
    int capacity;
    int minFrequency;

    LFUCache(int capacity): cache{}, frequencies{}, capacity(capacity), minFrequency(1) {
        cache.reserve(capacity);
    }
    //internal helper
    void insert(int key, int freq, int value) {
        frequencies[freq].insert(key);
        cache.emplace(key, freq, value);
    }

    void updateInsert(int key, int value) {
        auto [freq, value] = cache[key];
        frequencies[freq].erase(key);
        if (freq == minFrequency && frequencies[minFrequency].empty())
            ++minFrequency;
        ++freq;
        insert(key, freq, value);
    }

    int get(int key) {
        if (!cache.contains(key)) return -1;
        updateInsert(key, cache[key].second);
        return cache[key].second;
    }

    void put(int key, int value) {
        if (cache.contains(key)) {
            updateInsert(key, value);
        } else if (cache.size() == capacity) {
            //pop the end off of here and erase from cache
            int toPop = *frequencies[minFrequency].begin();
            frequencies[minFrequency].erase(toPop);
            cache.erase(toPop);
        } else {
            insert(key, 1, value);
        }
    }
};

int main() {

}
