
#include <vector>

int maxSubArray(const std::vector<int>& nums) {
    int currentSum = 0;
    int maxSum = 0;
    for (int num : nums) {
        if (currentSum < 0) currentSum = 0;
        currentSum += num;
        maxSum = std::max(currentSum, maxSum);
    }
    return maxSum;
}

bool canJump(const std::vector<int>& nums) {
    int goal = nums.size() - 1;
    while (goal > 0) {
        int i = goal-1;
        while (i+nums[i] < goal) {
            i--;
            if (i < 0) return false;
        }
        goal = i;
    }
    return true;
}

int minJumps(const std::vector<int>& nums) {
    int minJumps = 1;
    int l = 0, r = 0;
    while (r < nums.size()-1) {
        int furthest = 0;
        for (; l <= r; ++l) {
            furthest = std::max(l+nums[l], furthest);
        }
        l = r+1;
        r = furthest;
        ++minJumps;
    }
    return minJumps;
}

int main() {
    return 0;
}
