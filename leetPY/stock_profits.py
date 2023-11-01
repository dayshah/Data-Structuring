
# can only buy and sell once
def maxProfit(prices: list):
    maxProf = 0
    minPrice = prices[0]
    for price in prices:
        maxProf = max(maxProf, price-minPrice)
        minPrice = min(price, minPrice)
    return maxProf

# can buy and sell multiple times, only holding one at a time
def maxProfit2(prices: list):
    profit = 0
    for i in range(1, len(prices)):
        if prices[i] > prices[i-1]:
            profit += (prices[i] - prices[i-1])
    return profit

# can only buy and sell twice
def maxProfit3(prices: list):
    leftMin = prices[0]
    rightMax = prices[-1]
    leftProfits = {0: 0}
    rightProfits = {len(prices)-1: 0}

    l = 1
    r = len(prices) - 2
    while l < len(prices):
        leftProf = prices[l] - leftMin
        leftProfits[l] = max(leftProfits[l-1], leftProf)
        leftMin = min(leftMin, prices[l])
        l += 1

        rightProf = rightMax - prices[r]
        rightProfits[r] = max(rightProfits[r+1], rightProf)
        rightMax = max(rightMax, prices[r])
        r -= 1
    
    maxProf = 0
    for i in range(len(prices)):
        profit = leftProfits[i] + rightProfits[i]
        maxProf = max(profit, maxProf)
    return maxProf
