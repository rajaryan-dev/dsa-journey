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
//
// Beginner intuition: try EVERY possible pair of (buy day, sell day)
// where sell day comes after buy day. For each pair, calculate the
// profit and keep track of the biggest one seen so far.
//
// Note: outer loop runs to n-1 (not n) because when i = n-1 (last day),
// there's no day left after it to sell on — the inner loop would never
// execute anyway, so we skip that wasted iteration.
// ---------------------------------------------------------------------------
int maxProfitBrute(vector<int>& prices) {
  int n = prices.size();
  int maxProfit = 0;

  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      int profit = prices[j] - prices[i];
      maxProfit = max(maxProfit, profit);
    }
  }

  return maxProfit;
}

// ---------------------------------------------------------------------------
// Approach 2: Single Pass (Optimal) -> O(n) time, O(1) space
//
// Beginner intuition: imagine you're watching stock prices day by day.
//   - If today's price is LOWER than the cheapest you've seen so far,
//     that becomes your new "best day to buy" (update minPrice).
//   - Otherwise, today could be a good day to SELL — check if selling
//     today (using the cheapest buy price so far) beats your best
//     profit found until now.
//
// Why we don't check profit on the same day we update minPrice:
//   If today IS the new minimum, selling today would mean
//   profit = today's price - today's price = 0, which can never
//   improve our answer. So there's no need to check it that day.
// ---------------------------------------------------------------------------
int maxProfitOptimal(vector<int>& prices) {
  int n = prices.size();
  int profit = 0;
  int minPrice = prices[0];

  for (int i = 1; i < n; i++) {
    if (prices[i] < minPrice) {
      minPrice = prices[i];
    } else {
      profit = max(profit, prices[i] - minPrice);
    }
  }

  return profit;
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