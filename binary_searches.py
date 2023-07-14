
def search(nums: list[int], target: int):
    low = 0
    high = len(nums) - 1
    while (low <= high):
        mid = low + int((high-low)/2)
        if (target < nums[mid]):
            high = mid-1
        elif (target > nums[mid]):
            low = mid+1  
        else:
            return mid          
    return -1

def searchMatrix(matrix: list[list[int]], target: int):
    l = 0
    r = len(matrix) - 1
    row = -1
    while (l <= r):
        mid = l + int((r-l)/2)
        if (target < matrix[mid][0]):
            r = mid - 1
        elif (target > matrix[mid][-1]):
            l = mid + 1
        else:
            row = mid
            break
    l = 0
    r = len(matrix[row]) - 1
    while (row != -1 and l <= r):
        mid = l + int((r-l)/2)
        if (target < matrix[row][mid]):
            r = mid - 1
        elif (target > matrix[row][mid]):
            l = mid + 1
        else:
            return True
    return False

import math

def minEatingSpeed(piles: list[int], h: int):
    result = max(piles)
    avgPerPile = math.floor(h / len(piles))
    if avgPerPile == 0:
        return result
    maxNeededSpeed = math.ceil(result / avgPerPile)
    l, r = 1, maxNeededSpeed
    while l <= r:
        mid = l + int((r-l)/2)
        i, hours = 0, 0
        while hours <= h and i < len(piles):
            hours += math.ceil(piles[i]/mid)
            i += 1
        if i == len(piles) and hours <= h:
            result = min(result, mid)
            r = mid-1
        else:
            l = mid+1
    return result


