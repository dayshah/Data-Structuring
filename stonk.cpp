
#include <iostream>
#include <span>
#include <vector>
#include <climits>

// buy on a day and sell on another day in future
int maxProfit(const std::vector<int>& prices) {
    int maxProfit = 0;
    int currentMin = INT_MAX;
    for (int price : prices) {
        maxProfit = std::max(maxProfit, price - currentMin);
        currentMin = std::min(currentMin, price);
    }
    return maxProfit;
}

// can only hold one stock at a time
int maxProfit2(const std::vector<int>& prices) {
    int profit = 0;
    for (int i = 0; i < prices.size()-1; ++i) {
        if (prices[i+1] > prices[i]) profit += (prices[i+1] - prices[i]);
    }
    return profit;
}

// at most two transactions
int maxProfit3(const std::vector<int>& prices) {
    const size_t n = prices.size();
    int left[n];  left[0] = 0;
    int right[n+1]; right[n-1] = 0; right[n] = 0;
    int l = 1;
    int r = n-2;
    int leftMin = prices[0];
    int rightMax = prices[n-1];
    while (l < n) {
        left[l] = std::max(left[l-1], prices[l] - leftMin);
        leftMin = std::min(leftMin, prices[l]);
        
        right[r] = std::max(right[r+1], rightMax - prices[r]);
        rightMax = std::max(rightMax, prices[r]);

        ++l; --r;
    }
    int maxProfit = 0;
    for (int i = 0; i < n; ++i)
        maxProfit = std::max(maxProfit, left[i] + right[i+1]);

    return maxProfit;
}
#include <map>
#include <tuple>
// at most k transactions
int maxProfit4(int k, const std::vector<int>& prices) {
    //day_number, transactions_left, is_holding_stock
    std::map<std::tuple<int,int,int>, int> dp{};
    //dp[std::make_tuple(i,j,1)] = dp[i-1][j][1]
    //dp[std::make_tuple(i,j,1)] = dp[i-1][j-1][0]
    //dp[std::make_tuple(i,j,0)] = dp[i-1][j][0]
    //dp[std::make_tuple(i,j,0)] = dp[i-1][j][0]
    return 0;
}

// after selling, can't buy on the next day, one day cooldown
int maxProfitCooldown(const std::vector<int>& prices) {
    int reset=0, held=INT_MIN, sold=INT_MIN;
    for (int price : prices) {
        int prev_sold = sold;
        sold = held + price;
        held = std::max(held, reset-price);
        reset = std::max(reset, prev_sold);
    }
    return std::max(sold, reset);
}

int main() {
    std::cout << maxProfitCooldown({1,2,3,0,2}) << "\n";
}
