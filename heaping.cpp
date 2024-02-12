#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

// task scheduler
int leastInterval(const std::vector<char>& tasks, int n) { // n = cooldown
    std::unordered_map<char, int> counter{};
    for (char c : tasks) counter[c]++;
    std::priority_queue<std::pair<int,char>> taskCounts{};
    for (const auto& [c, count] : counter) {
        taskCounts.emplace(count, c);
    }
    int time = 0;
    char lastTask = '-';
    std::queue<std::tuple<int, char, int>> onCooldown{}; // timeUntil, task, count
    while (taskCounts.size() > 0 || onCooldown.size() > 0) {
        if (taskCounts.size() == 0) time = std::get<0>(onCooldown.front());
        if (taskCounts.size() > 0) {
            auto [count, task] = taskCounts.top();
            taskCounts.pop();
            if (count-1 > 0) onCooldown.emplace(time+n, task, count-1);
        }
        while (onCooldown.size() > 0 && std::get<0>(onCooldown.front()) <= time) {
            auto [timeUntil, task, count] = onCooldown.front();
            onCooldown.pop();
            taskCounts.emplace(count, task);
        }
        ++time;
    }
    return time;
}
