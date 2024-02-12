#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <functional>

int minCostConnectPoints(const std::vector<std::vector<int>>& points) {
    typedef std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>> DistPointHeap; // [(dist,point)...]
    std::unordered_map<int, std::vector<std::pair<int,int>>> adjList{};
    for (int i = 0; i < points.size(); ++i) {
        for (int j = i+1; j < points.size(); ++j) {
            int dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
            adjList[i].emplace_back(dist, j);
            adjList[j].emplace_back(dist, i);
        }
    }
    std::unordered_set<int> visited{};
    DistPointHeap distPointHeap{};
    distPointHeap.emplace(0,0);
    int minCost = 0;
    while (visited.size() < points.size()) {
        const auto [distToStart, start] = distPointHeap.top();
        distPointHeap.pop();
        if (!visited.contains(start)) {
            minCost += distToStart;
            visited.insert(start);
            for (const auto& [dist, end] : adjList[start]) {
                if (!visited.contains(end)) distPointHeap.emplace(dist, end);
            }
        }
    }
    return minCost;
}

int networkDelayTime(const std::vector<std::vector<int>>& times, int n, int k) {
    std::unordered_map<int, std::vector<std::pair<int,int>>> adjList{}; // source -> dest,time
    for (const auto& time : times) {
        adjList[time[0]].emplace_back(time[1], time[2]);
    }
    int time = 0;
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>> timeDestHeap{};
    timeDestHeap.emplace(0,k);
    std::unordered_set<int> visited{};
    while (timeDestHeap.size() > 0) {
        const auto [currTime, current] = timeDestHeap.top();
        timeDestHeap.pop();
        if (visited.contains(current)) continue;
        visited.insert(current);
        time = std::max(time, currTime);
        if (visited.size() == n) return time;
        for (const auto& [dest, time] : adjList[current]) {
            if (!visited.contains(dest)) timeDestHeap.emplace(currTime+time, dest);
        }
    }
    return -1;
}

int findCheapestPrice(int n, const std::vector<std::vector<int>>& flights, int src, int dst, int k) {
    std::vector<int> prices(n+1, INT32_MAX);
    for (int stop = -1; stop <= k; ++stop) {
        std::vector<int> tempPrices = prices;
        for (const auto& flight : flights) {
            int start = flight[0], end = flight[1], price=flight[2];
            if (prices[start] == INT32_MAX) continue;
            else tempPrices[end] = std::min(prices[start]+price, tempPrices[end]);
        }
        prices = std::move(tempPrices);
    }
    return prices[dst] == INT32_MAX ? -1 : prices[dst];
}

int main() {
    std::cout << "Hello, world!" << std::endl;
    return 0;
}

