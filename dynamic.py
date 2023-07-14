

def climbStairs(n: int) -> int:
    dp = {}
    dp[1] = 1
    dp[2] = 2
    i = 3
    while i <= n:
        dp[i] = dp[i-1] + dp[i-2]
        i+=1
    return dp[n]

def minCostClimbingStairs(cost: list[int]) -> int:
    dp = {}
    dp[1] = cost[0]
    dp[2] = cost[1]
    i = 3
    while i <= len(cost):
        dp[i] = min(dp[i-1], dp[i-2]) + cost[i-1]
        i += 1
    return min(dp[i-1], dp[i-2])

def rob(nums: list[int]) -> int:
    if len(nums) < 3:
        return max(nums)
    dp = {}
    dp[0] = nums[0]
    dp[1] = nums[1]
    dp[2] = nums[2] + nums[0]
    i = 3
    while i < len(nums):
        dp[i] = nums[i] + max(dp[i-2], dp[i-3])
        i += 1
    return max(dp[i-1],dp[i-2])

def rob2(nums: list[int]) -> int:
    if len(nums) < 3:
            return max(nums)
    return max(rob(nums[1:]), rob(nums[:-1]))

def longestPalindrome(s: str) -> str:
    result = ""
    maxLen = 0
    for i in range(len(s)):
        l = i
        r = i
        while l >= 0 and r < len(s) and s[l] == s[r]:
            if (r-l) > maxLen:
                result = s[l:r+1]
                maxLen = r-l
            l -= 1
            r += 1
        l2 = i
        r2 = i+1
        while l2 >= 0 and r2 < len(s) and s[l2] == s[r2]:
            if (r2-l2) > maxLen:
                result = s[l2:r2+1]
                maxLen = r2-l2
            result += 1
            l2 -= 1
            r2 += 1
    return result

def countPalindromes(s: str) -> int:
    result = 0
    for i in range(len(s)):
        l = i
        r = i
        while l >= 0 and r < len(s) and s[l] == s[r]:
            result += 1
            l -= 1
            r += 1
        l2 = i
        r2 = i+1
        while l2 >= 0 and r2 < len(s) and s[l2] == s[r2]:
            result += 1
            l2 -= 1
            r2 += 1
    return result

