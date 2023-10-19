
#include <iostream>
#include <queue>
#include <unordered_set>

// time for all 
int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k) {
    std::unordered_map<
        int,
        std::vector<std::pair<int,int>>
    > adjList{};
    adjList.reserve(n);
    for (std::vector<int>& time : times) {
        int source = time[0];
        int dest = time[1];
        int weight = time[2];
        adjList[source].emplace_back(weight, dest);
    }

    std::priority_queue<
        std::pair<int,int>,
        std::vector<std::pair<int,int>>,
        std::greater<std::pair<int,int>>
    > queue;
    queue.emplace(0, k);
    std::unordered_set<int> visited;
    visited.reserve(n);
    int result = 0;
    while (queue.size() > 0) {
        auto [dist, node] = queue.top();
        queue.pop();
        if (visited.contains(node)) continue;
        visited.insert(node);
        result = std::max(result, dist);
        for (auto [weight, dest] : adjList[node]) {
            if (!visited.contains(dest)) queue.emplace(dist+weight, dest);
        }
    }
    return visited.size() == n ? result : -1;
}

int main() {
    std::cout << "hello" << "\n";
}
