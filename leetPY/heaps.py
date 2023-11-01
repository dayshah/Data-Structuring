import heapq

class KthLargest:

    def __init__(self, k: int, nums: list[int]):
        self.nums = nums
        heapq.heapify(self.nums)
        self.k = k
        while (len(self.nums) > self.k):
            heapq.heappop(self.nums)

    def add(self, val: int):
        heapq.heappush(self.nums, val)
        while (len(self.nums) > self.k):
            heapq.heappop(self.nums)
        return self.nums[0]

def lastStoneWeight(self, stones: list[int]):
    stones = [-x for x in stones]
    heapq.heapify(stones)
    while (len(stones) > 1):
        big = heapq.heappop(stones)
        bigTwo = heapq.heappop(stones)
        if big != bigTwo:
            heapq.heappush(stones, big-bigTwo)
    if stones:  
        return -stones[0]
    else:
        return 0

def kClosest(points: list[list[int]], k: int):
    distances = []
    for x, y in points:
        dist = (abs(x - 0) ** 2) + (abs(y - 0) ** 2)
        distances.append([dist, x, y])
    heapq.heapify(distances)
    res = []
    for i in range(k):
        dist, x, y = heapq.heappop(distances)
        res.append([x, y])
    return res

def kLargest(nums: list[int], k: int):
    heap = [-x for x in nums]
    heapq.heapify(heap)
    res = nums[0]
    for i in range(k):
        res = -heapq.heappop(heap)
    return res
