#include <iostream>
#include <deque>
#include <unordered_set>

using namespace std;

bool validTree(int n, const vector<vector<int>>& edges) {
    unordered_map<int, vector<int>> adjList {};
    for (const vector<int>& edge : edges) {
        adjList[edge[0]].push_back(edge[1]);
        adjList[edge[1]].push_back(edge[0]);
    }
    deque<int> deck{};
    unordered_map<int, int> visited{};
    deck.push_back(0);
    ++visited[0];
    while (deck.size() > 0) {
        int node = deck[0];
        deck.pop_front();
        for (const int next : adjList[node]) {
            cout << (next) << endl;
            if (visited[next] == 2) {
                return false;
            }
            ++visited[next];
            deck.push_back(next);
        }
    }
    return visited.size() == n-1;
}

int main() {
    cout << "hello" << endl;
    vector<vector<int>> edges {{0,1},{0,2},{0,3},{1,4}};
    int n = 5;
    cout << validTree(n, edges) << endl;
}
