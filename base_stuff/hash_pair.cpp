
#include <iostream>

struct HashPair {
    auto operator()(const std::pair<int,int>& p) const {
        if (p.first == p.second) return std::hash<int>()(p.first);
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
};
