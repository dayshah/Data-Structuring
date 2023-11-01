
def isPalindrome(s: str):
    l = 0
    r = len(s)-1
    s = s.lower()
    while l <= r:
        if not s[l].isalnum():
            l += 1
            continue
        if not s[r].isalnum():
            r -= 1
            continue
        if s[l] != s[r]:
            return False
        l += 1
        r -= 1
    return True

def twoSumSorted(nums: list, target: int):
    l = 0
    r = len(nums) - 1
    while l < r:
        attempt = nums[l] + nums[r]
        if attempt > target:
            r -= 1
        elif attempt < target:
            l += 1
        else:
            return [l+1, r+1]
    return []

def threeSum(nums: list):
    nums.sort()
    result = set()
    i = 0
    while i < len(nums) and nums[i] <= 0:
        if i > 0 and nums[i-1] == nums[i]:
            i += 1
            continue
        l = i + 1
        r = len(nums) - 1
        target = 0-nums[i]
        while l < r:
            add = nums[l] + nums[r]
            if add < target:
                l += 1
            elif add > target:
                r -= 1
            else:
                result.add((nums[i], nums[l], nums[r]))
                l += 1
        i += 1
    return list(result)

def mostWater(heights: list):
    maxArea = 0
    l = 0
    r = len(heights) - 1
    while l < r:
        area = min(heights[l], heights[r]) * (r-l)
        if area > maxArea:
            maxArea = area
        if heights[l] < heights[r]:
            l += 1
        else:
            r -= 1
    return maxArea

# min(maxL, maxR) - heights[i]
def trappingWater(heights: list):
    l = 0
    r = len(heights) - 1
    maxL = heights[l]
    maxR = heights[r]
    trapped = 0
    while l < r:
        if maxR < maxL:
            water = maxR - heights[r]
            trapped += max(0, water)
            r -= 1
            maxR = max(heights[r], maxR)
        else:
            water = maxL - heights[l]
            trapped += max(0, water)
            l += 1
            maxL = max(heights[l], maxL)
    return trapped

# find longest palindrome
def longestPalindrome(s: str) -> str:
    result = ""
    maxLen = 0
    for i in range(len(s)):
        # expand from the center for each index
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
            l2 -= 1
            r2 += 1
    return result

# basically doing the same thing as last problem
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
