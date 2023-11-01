#include <iostream>
#include <unordered_set>

struct UnionFind {
    std::unordered_map<int, int> parentOf;
    int numComponents;

    UnionFind(int n): parentOf(n), numComponents(n) {
        for (int i = 1; i <= n; ++i) parentOf[i] = i;
    }

    int getPar(int x) {
        if (parentOf.contains(x)) return parentOf[x];
        else return x;
    }

    int find(int x) {
        while (getPar(x) != x) {
            parentOf[x] = getPar(getPar(x));
            x = getPar(x);
        }
        return x;
    }

    bool isSameComponent(int x, int y) {
        if (find(x) == find(y)) return true;
        else return false;
    }

    bool _union(int x, int y) {
        int parX = find(x);
        int parY = find(y);
        if (parX == parY) return false;
        
        if (parX > parY) parentOf[parY] = parX;
        else parentOf[parX] = parY;
        --numComponents;
        return true;
    }

    int getNumComponents() {
        return numComponents;
    }
};

int main() {
    UnionFind uf(10);
    std::cout << uf.find(1) << "\n";
    std::cout << uf.isSameComponent(1,3) << "\n";
    std::cout << uf._union(1,2) << "\n";
    std::cout << uf._union(2,3) << "\n";
    std::cout << uf.getNumComponents() << "\n";
    std::cout << uf.isSameComponent(1,3) << "\n";
}
