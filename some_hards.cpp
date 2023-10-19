
#include <iostream>
#include <unordered_set>
#include <unordered_map>

int longestNonDecreasing(const std::vector<int>& nums1, const std::vector<int>& nums2) {
    int dp1 = 1;
    int dp1Future = 1;
    int dp2 = 1;
    int res = 1;
    for (int i = 1; i < nums1.size(); ++i) {
        dp1Future = std::max(
            nums1[i] >= nums1[i-1] ? dp1+1 : 1,
            nums1[i] >= nums2[i-1] ? dp2+1 : 1
        );
        dp2 = std::max(
            nums2[i] >= nums1[i-1] ? dp1+1 : 1,
            nums2[i] >= nums2[i-1] ? dp2+1 : 1
        );
        dp1 = dp1Future;
        res = std::max({res, dp1, dp2});
    }
    return res;
}

int goodBinaryStrings(int minLength, int maxLength, int oneGroup, int zeroGroup) {
    int mod = (int)std::powf(10,9) + 7;
    int dp[maxLength];
    dp[0] = 1;
    int res = 0;
    for (int i = 1; i < maxLength; ++i) {
        if (i >= oneGroup) dp[i] += dp[i - oneGroup];
        if (i >= zeroGroup) dp[i] += dp[i - zeroGroup];
        if (i >= minLength) res += static_cast<int>(dp[i] % mod);
    }
    return res;
}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    ~TreeNode() { delete left; delete right; }
};

int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    std::function<int(TreeNode*)> func;
    func = [&maxSum, &func](TreeNode* node){
        if (!node) return 0;
        int leftGain = std::max(func(node->left), 0);
        int rightGain = std::max(func(node->right), 0);
        int gain = leftGain + rightGain + node->val;
        maxSum = std::max(maxSum, gain);
        return gain;
    };
    func(root);
    return maxSum;
}

int lenLongestFibSubsequence(const std::vector<int>& arr) {
    const int N = arr.size();
    std::unordered_set<int> numSet(arr.begin(), arr.end());
    std::unordered_map<int, std::unordered_map<int,int>> dp{};
    dp.reserve(N);

    int result = 0;
    for (int i = 0; i < N; ++i) {
        int big = arr[i];
        dp.emplace(i, std::unordered_map<int,int>());
        for (int j = 0; j < i; ++j) {
            int num2 = arr[j];
            int num1 = big - num2;
            if (num1 < num2 && numSet.contains(num1)) {
                if (dp[num1].contains(num2))
                    dp[num2][big] = dp[num1][num2] + 1;
                else
                    dp[num2][big] = 3;
                result = std::max(result, dp[num2][big]);
            }
        }
    }
    return result > 2 ? result : 0;
}

int minKnightMoves(int x, int y) {
    std::unordered_map<int, std::unordered_map<int,int>> dp{};
    std::function<int(int,int)> dfs;
    dfs = [&dfs, &dp](int i, int j) {
        if (dp.contains(i) && dp[i].contains(j)) 
            return dp[i][j];
        else if (i+j == 0)
            return 0;
        else if (i+j == 2)
            return 2;
        else {
            dp[i][j] = std::min(
                dfs(abs(i-1), abs(j-2)),
                dfs(abs(i-2), abs(j-1))
            ) + 1;
            return dp[i][j];
        }
    };
    return dfs(abs(x), abs(y));
}

int deleteAndEarn(std::vector<int>& nums) {
    std::unordered_map<int, int> points{};
    int maxNum = 0;
    for (int num : nums) {
        points[num] += num;
        maxNum = std::max(num, maxNum);
    }
    std::unordered_map<int,int> dp{};
    std::function<int(int)> maxPoints;
    maxPoints = [&dp, &points, &maxPoints] (int num) {
        if (dp.contains(num)) return dp[num];
        else if (num == 0) return 0;
        else if (num == 1) return points[1];
        else {
            dp[num] = std::max(
                maxPoints(num-1),
                maxPoints(num-2) + points[num]
            );
            return dp[num];
        }
    };
    return maxPoints(maxNum);
}

double knightProbability(int n, int k, int row, int column) {
    return -1;
}

int subarraysDivByK(std::vector<int>& nums, int k) {
    int result = 0;
    int prefixMod = 0;
    std::unordered_map<int, int> modGroups{};
    modGroups[0] = 1;
    for (int num : nums) {
        prefixMod += (num % k + k);
        prefixMod %= k;
        result += modGroups[prefixMod];
        ++modGroups[prefixMod];
    }
    return result;
}

int main() {
    std::cout << minKnightMoves(2,1) << std::endl;
    std::cout << 3%5 << std::endl;
}
