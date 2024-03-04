
#include <iostream>
#include <list>
#include <ostream>
#include <string>
#include <unordered_map>

template <typename K, typename V>
class OrderedDictionary {
    //typedef std::unordered_map<K,V>::iterator map_iterator;
    typedef std::list<const K*>::iterator list_iterator;

    private:
    std::unordered_map<K, V> map;
    std::list<const K*> list;
    std::unordered_map<const K*, list_iterator> iteratorMap;

    public:
    void push_back(const std::pair<K,V>& pair) {
        map.insert(pair);
        const K* key_ptr = &(map.find(pair.first)->first);
        list.push_back(key_ptr);
        iteratorMap.insert(key_ptr, list.end()-1);
    }
    void push_back(std::pair<K,V>&& pair) {
        map.insert(pair);
        const K* key_ptr = &(map.find(pair.first)->first);
        list.push_back(key_ptr);
        //iteratorMap.insert(key_ptr, list.end()-1);
    }
    bool remove_key(const K& key) {
        const auto& foundIter = map.find(key);
        const K* key_ptr = &(foundIter->first);
        if (foundIter != map.end()) {
            list.erase(iteratorMap.at(key_ptr));
            iteratorMap.erase(key_ptr);
            map.erase(foundIter);
            return true;
        }
        return false;
    }
    void printSizes() {
        std::cout << "list size: " << list.size() << std::endl;
        std::cout << "map size: " << map.size() << std::endl;
    }
};

int main() {
    OrderedDictionary<int, std::string> test{};
    test.push_back({1, "hi"});
    test.printSizes();
    test.remove_key(1);
    return 0;
}
