
def subsets(nums: list[int]):
    res = []
    subset = []
    def backtrack(i):
        if i >= len(nums):
            res.append(subset)
            return
        subset.append(nums[i])
        backtrack(i+1)
        subset.pop()
        backtrack(i+1)
    backtrack(0)
    return res

import itertools
def subsetsIter(nums: list[int]):
    res = []
    for i in range(len(nums)+1):
        res += list(itertools.combinations(nums, i))
    return res

