import collections 

# top k most frequent elements in nums
def topKFrequent(nums, k):
    frequency_map = collections.Counter(nums)
    sorted_by_frequency = list(frequency_map.keys())
    sorted_by_frequency.sort(key=lambda num: -frequency_map[num])
    result = []
    for i in range(k):
        result.append(sorted_by_frequency[i])
    return result

# a list of products where products[i] is product of all except nums[i]
def productExceptSelf(nums):
    products = []
    # prefix product of everything
    pre = 1
    for i in range(len(nums)):
        products.append(pre)
        pre *= nums[i]
    # postfix product of everything
    post = 1
    for i in range(len(nums)-1, -1, -1):
        products[i] *= post
        post *= nums[i]
    return products

# encode a list of strings
def encode(strList):
    result = ""
    for word in strList:
        num = len(word)
        result += str(num)
        result += "#"
        result += word
    return result
# decode that list of strings
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

# length of the longest sequence of consecutive elements that can be made from nums
def longestConsecutive(nums):
    nums = set(nums)
    longest = 0
    while nums:
        currentLen = 1
        original_num = nums.pop()
        # pick a random num and check if there's a sequence around it and get length of it
        num = original_num
        while num - 1 in nums:
            num -= 1
            nums.remove(num)
            currentLen += 1
        num = original_num
        while num + 1 in nums:
            num += 1
            nums.remove(num)
            currentLen += 1
        longest = max(currentLen, longest)
    return longest

# number of possible subarrays that add up to k
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
