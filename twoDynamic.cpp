#include <iostream>

using namespace std;

int uniquePaths(int m, int n) {
    unordered_map<int, unordered_map<int, int>> paths {};
    paths[m-1][n-1] = 1;
    for (int ni = 0; ni < n-1; ni++) {
        paths[m-1][ni] = 1;
    }
    for (int mi = 0; mi < m-1; mi++) {
        paths[mi][n-1] = 1;
    }
    for (int mi = m-2; mi >= 0; mi--) {
        for (int ni = n-2; ni >= 0; ni--) {
            int down = 0;
            if (mi+1 < m) down = paths[mi+1][ni];
            int right = 0;
            if (ni+1 < n) right = paths[mi][ni+1];
            paths[mi][ni] = down + right;
        }
    }
    return paths[0][0];
}



int main() {
    cout << uniquePaths(3, 7) << endl;
}

