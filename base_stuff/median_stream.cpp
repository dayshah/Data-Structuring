
#include <unordered_map>
#include <iostream>
#include <queue>

struct MedianStream {
    // biggest at top
    std::priority_queue<int, std::vector<int>, std::less<int>> smaller;
    // smallest at top
    std::priority_queue<int, std::vector<int>, std::greater<int>> bigger;

    void addNum(int num) {
        if (!smaller.empty() && num > smaller.top()) {
            bigger.push(num);
            if (bigger.size() - smaller.size() == 2) {
                smaller.push(bigger.top());
                bigger.pop();
            }
        } else {
            smaller.push(num);
            if (smaller.size() - bigger.size() == 2) {
                bigger.push(smaller.top());
                smaller.pop();
            }
        }
    }

    double getMedian() {
        if (smaller.size() == bigger.size())
            return ((smaller.top() + bigger.top()) / 2.0);
        else if (smaller.size() > bigger.size())
            return smaller.top();
        else
            return bigger.top();
    }
};

int main() {
    MedianStream ms;
    ms.addNum(1);
    //std::cout << ms.getMedian() << "\n";
    ms.addNum(2);
    std::cout << ms.getMedian() << "\n";

    std::priority_queue<std::pair<int,int>> attempt;
    attempt.emplace(1,2);
    attempt.emplace(3,4);
    std::cout << attempt.top().first << "\n";
}

