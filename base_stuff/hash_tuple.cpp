
#include <tuple>

struct HashThreeTuple {
    long operator()(const std::tuple<int,int,int>& tup) {
        return std::get<0>(tup) ^ std::get<1>(tup) ^ std::get<2>(tup);
    }
};
