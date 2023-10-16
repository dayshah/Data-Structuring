
#include <iostream>
#include <map>

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
    int maxSum = -INFINITY;
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


int main() {
    std::cout << goodBinaryStrings(3,3,1,1) << std::endl;
}
