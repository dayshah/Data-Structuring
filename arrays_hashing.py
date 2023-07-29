import collections 

def topKFrequent(nums, k):
    frequency_map = collections.Counter(nums)
    sorted_by_frequency = list(frequency_map.keys())
    sorted_by_frequency.sort(key=lambda num: -frequency_map[num])
    result = []
    for i in range(k):
        result.append(sorted_by_frequency[i])
    return result

def productExceptSelf(nums):
    output = []
    pre = 1
    for i in range(len(nums)):
        output.append(pre)
        pre *= nums[i]
    post = 1
    for i in range(len(nums)-1, -1, -1):
        output[i] *= post
        post *= nums[i]
    return output

def encode(strList):
    result = ""
    for word in strList:
        num = len(word)
        result += str(num)
        result += "#"
        result += word
    return result

def decode(strToDecode):
    result = []
    i = 0
    while i < len(strToDecode):
        num = ""
        while strToDecode[i] != "#":
            num += strToDecode[i]
            i += 1
        num = int(num)
        i += 1
        word = strToDecode[i : i+num]
        result.append(word)
        i += num
    return result

def longestConsecutive(nums):
    nums = set(nums)
    longest = 0
    while nums:
        current = 1
        original_num = nums.pop()
        num = original_num
        while num - 1 in nums:
            num -= 1
            nums.pop(num)
            current += 1
        num = original_num
        while num + 1 in nums:
            num += 1
            nums.remove(num)
            current += 1
        longest = max(current, longest)
    return longest

def subarraySum(nums: list[int], k: int):
    count = 0
    sum = 0
    occurenceMap = collections.defaultdict(int)
    occurenceMap[0] = 1
    for num in nums:
        sum += num
        count += occurenceMap[sum-k]
        occurenceMap[sum] += 1
    return count
