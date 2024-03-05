
#include <functional>
#include <iostream>
#include <list>
#include <ostream>
#include <string>
#include <unordered_map> 

template <typename K, typename V>
class OrderedDictionary {
    typedef std::list<std::pair<K,V>>::const_iterator list_iterator;
    typedef std::unordered_map<K,list_iterator>::const_iterator map_iterator;

    private:
    std::unordered_map<K, list_iterator> map;
    std::list<std::pair<K,V>> list;

    public:
    void push_back(const std::pair<K,V>& pair) {
        list.push_back(pair);
        map.insert({pair.first, std::prev(list.end())});
    }
    void push_back(std::pair<K,V>&& pair) {
        list.push_back({pair.first, std::move(pair.second)});
        map.insert({std::move(pair.first), std::prev(list.end())});
    }
    bool remove_key(const K& key) {
        const auto& map_iter = map.find(key);
        if (map_iter != map.end()) {
            list.erase(map_iter->second);
            map.erase(map_iter);
            return true;
        }
        return false;
    }
    const V& get_back_value() const {
        return list.back().second;
    }
    const V& get_value_for_key(const K& key) const {
        return map.at(key)->second;
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
    std::cout << "\n" << test.get_back_value() << "\n";
    std::cout << test.get_value_for_key(1) << "\n\n";
    test.remove_key(1);
    test.printSizes();
    return 0;
}
