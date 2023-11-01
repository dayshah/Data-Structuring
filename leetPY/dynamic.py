
# how many ways to climb up a staircase with n steps
def climbStairs(n: int) -> int:
    dp = {}
    dp[1] = 1
    dp[2] = 2
    i = 3
    while i <= n:
        dp[i] = dp[i-1] + dp[i-2]
        i+=1
    return dp[n]

# minimum cost to climb up staircase of len(cost) steps
def minCostClimbingStairs(cost: list[int]) -> int:
    dp = {}
    dp[1] = cost[0]
    dp[2] = cost[1]
    i = 3
    while i <= len(cost):
        dp[i] = min(dp[i-1], dp[i-2]) + cost[i-1]
        i += 1
    return min(dp[i-1], dp[i-2])

# most you can rob while not breaking into adjacent houses
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

# same as previous but first and last houses are adjacent
def rob2(nums: list[int]) -> int:
    if len(nums) < 3:
            return max(nums)
    return max(rob(nums[1:]), rob(nums[:-1]))

import collections

# the fewest number of coins to make amount
def coinChange(coins: list[int], amount: int):
    dp = collections.defaultdict(lambda: float('inf'))
    dp[0] = 0
    for coin in coins:
        for x in range(coin, amount+1):
            dp[x] = min(dp[x], dp[x-coin]+1)
    
    return -1 if dp[amount] == float('inf') else dp[amount]

def coinChangeWays(coins: list[int], amount: int):
    dp = collections.defaultdict(lambda: 0)
    dp[0] = 1
    
    