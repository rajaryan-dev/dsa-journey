#include <climits>
#include <iostream>
#include <vector>
using namespace std;

/*
    Problem: 121. Best Time to Buy and Sell Stock
    Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

    You are given an array prices where prices[i] is the price of a
    given stock on the i-th day. You want to maximize profit by choosing
    a single day to buy and a different day in the future to sell.
    Return the max profit, or 0 if no profit is possible.

    Example:
    Input:  prices = [7,1,5,3,6,4]
    Output: 5
    Explanation: buy on day 2 (price=1), sell on day 5 (price=6),
                 profit = 6-1 = 5
*/

// ---------------------------------------------------------------------------
// Approach 1: Brute Force -> O(n^2) time, O(1) space
// Idea: try every (buy day, sell day) pair where sell day > buy day,
//       track the max profit seen.
// ---------------------------------------------------------------------------
int maxProfitBrute(vector<int>& prices) {
  int n = prices.size();
  int maxProfit = 0;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int profit = prices[j] - prices[i];
      maxProfit = max(maxProfit, profit);
    }
  }

  return maxProfit;
}

// ---------------------------------------------------------------------------
// Approach 2: Single Pass (Optimal) -> O(n) time, O(1) space
// Idea: track the minimum price seen SO FAR while scanning left to right.
//       At each day, the best possible profit if selling TODAY is
//       (today's price - minPriceSoFar). Track the max of these.
//
//       Why it works: for any sell day j, the best buy day is always
//       the minimum price among all days before j — no need to check
//       every pair, just carry the running minimum forward.
// ---------------------------------------------------------------------------
int maxProfitOptimal(vector<int>& prices) {
  int minPrice = INT_MAX;
  int maxProfit = 0;

  for (int price : prices) {
    minPrice = min(minPrice, price);               // cheapest buy so far
    maxProfit = max(maxProfit, price - minPrice);  // best profit if sold today
  }

  return maxProfit;
}

// ---------------------------------------------------------------------------
// Driver code (hardcoded test cases, no cin)
// ---------------------------------------------------------------------------
int main() {
  vector<vector<int>> testCases = {
      {7, 1, 5, 3, 6, 4},  // expected 5
      {7, 6, 4, 3, 1},     // expected 0 (prices only decrease)
      {2, 4, 1}            // expected 2
  };

  for (auto& prices : testCases) {
    vector<int> p1 = prices, p2 = prices;

    cout << "Brute Force -> Max Profit: " << maxProfitBrute(p1) << endl;
    cout << "Optimal     -> Max Profit: " << maxProfitOptimal(p2) << endl;
    cout << "-----------------------------------" << endl;
  }

  return 0;
}