
import collections

def longestWithoutRepeating(s: str) -> int:
    currentMap = {}
    longest = 0
    l = 0
    for i, c in enumerate(s):
        if c in currentMap:
            l = max(l, currentMap[c] + 1)
        currentMap[c] = i
        longest = max(i-l+1, longest)
    return longest 


def longestRepeatingWithReplacement(s: str, k: int) -> int:
    countMap = collections.defaultdict(int)
    mostFrequentCount = 0
    longest = 0
    l = 0
    for i, c in enumerate(s):
        countMap[c] += 1
        mostFrequentCount = max(mostFrequentCount, countMap[c])
        window = i - l + 1
        if window - mostFrequentCount <= k:
            longest = max(longest, window)
        else:
            countMap[s[l]] -= 1
            l += 1
    return longest

def containsPermutation(s1: str, s2: str) -> bool:
    toCheck = collections.Counter(s1);
    l = 0
    r = len(s1)
    countMap = collections.Counter(s2[0:r])
    if toCheck == countMap:
        return True
    while r < len(s2):
        if s2[r] not in countMap:
            countMap[s2[r]] = 0
        countMap[s2[r]] += 1
        countMap[s2[l]] -= 1
        if toCheck == countMap:
            return True
        l += 1
        r += 1
    return False

def minWindow(s: str, t: str) -> str:
    need = collections.Counter(t)
    have = collections.defaultdict(int)
    equalCount = 0
    minWindow = s + "a"
    l = 0
    for r in range(len(s)):
        have[s[r]] += 1
        if (s[r] in need) and (need[s[r]] == have[s[r]]):
            equalCount += 1
        while equalCount == len(need) and l <= r:
            window = s[l:r+1]
            have[s[l]] -= 1
            if have[s[l]] < need[s[l]]:
                equalCount -= 1
                if len(window) < len(minWindow):
                    minWindow = window
            l += 1

    if (len(minWindow) > len(s)):
        return ""
    else:
        return minWindow
    
def maxSlidingWindow(nums: list[int], k: int):
    if k == 1:
        return nums
    output = []
    deck = collections.deque()
    deck.append(0)
    i = 1
    while i < len(nums):
        if deck[0] < i-k+1:
            deck.popleft()
        while deck and nums[deck[-1]] < nums[i]:
            deck.pop()
        deck.append(i)
        if i >= k-1:
            output.append(nums[deck[0]])
        i += 1
    return output
