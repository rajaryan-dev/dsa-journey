#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    // Helper function for Pure Recursion
    int solveRec(int n, int x, int y, int z) {
        if (n == 0) return 0;
        if (n < 0) return INT_MIN;

        int a = solveRec(n - x, x, y, z);
        int b = solveRec(n - y, x, y, z);
        int c = solveRec(n - z, x, y, z);

        if (a != INT_MIN) a++;
        if (b != INT_MIN) b++;
        if (c != INT_MIN) c++;

        return max({a, b, c});
    }

    // Helper function for Memoization
    int solveMem(int n, int x, int y, int z, vector<int>& dp) {
        if (n == 0) return 0;
        if (n < 0) return INT_MIN;
        if (dp[n] != -1) return dp[n];

        int a = solveMem(n - x, x, y, z, dp);
        int b = solveMem(n - y, x, y, z, dp);
        int c = solveMem(n - z, x, y, z, dp);

        if (a != INT_MIN) a++;
        if (b != INT_MIN) b++;
        if (c != INT_MIN) c++;

        return dp[n] = max({a, b, c});
    }

public:
    // 1. Pure Recursion
    int maximizeTheCutsRecursion(int n, int x, int y, int z) {
        int ans = solveRec(n, x, y, z);
        return ans < 0 ? 0 : ans;
    }

    // 2. Memoization (Top-Down DP)
    int maximizeTheCutsMemoization(int n, int x, int y, int z) {
        vector<int> dp(n + 1, -1);
        int ans = solveMem(n, x, y, z, dp);
        return ans < 0 ? 0 : ans;
    }

    // 3. Tabulation (Bottom-Up DP)
    int maximizeTheCutsTabulation(int n, int x, int y, int z) {
        vector<int> dp(n + 1, -1);
        dp[0] = 0; 

        for (int i = 1; i <= n; i++) {
            if (i >= x && dp[i - x] != -1) dp[i] = max(dp[i], dp[i - x] + 1);
            if (i >= y && dp[i - y] != -1) dp[i] = max(dp[i], dp[i - y] + 1);
            if (i >= z && dp[i - z] != -1) dp[i] = max(dp[i], dp[i - z] + 1);
        }

        return dp[n] == -1 ? 0 : dp[n]; 
    }

    // 4. Space Optimization
    // (Note: For this problem, O(n) is already the absolute optimal space. 
    // It cannot be reduced to O(1) like Fibonacci because x, y, z can be up to n.
    // So this is identical to tabulation, but included for completeness!)
    int maximizeTheCutsSpaceOptimized(int n, int x, int y, int z) {
        vector<int> dp(n + 1, -1);
        dp[0] = 0; 

        for (int i = 1; i <= n; i++) {
            if (i >= x && dp[i - x] != -1) dp[i] = max(dp[i], dp[i - x] + 1);
            if (i >= y && dp[i - y] != -1) dp[i] = max(dp[i], dp[i - y] + 1);
            if (i >= z && dp[i - z] != -1) dp[i] = max(dp[i], dp[i - z] + 1);
        }

        return dp[n] == -1 ? 0 : dp[n]; 
    }
};

int main() {
    Solution sol;
    
    cout << "--- Recursion ---" << endl;
    cout << "Output: " << sol.maximizeTheCutsRecursion(5, 5, 3, 2) << "\n\n"; 
    
    cout << "--- Memoization ---" << endl;
    cout << "Output: " << sol.maximizeTheCutsMemoization(5, 5, 3, 2) << "\n\n"; 

    cout << "--- Tabulation ---" << endl;
    cout << "Output: " << sol.maximizeTheCutsTabulation(5, 5, 3, 2) << "\n\n"; 

    cout << "--- Space Optimized ---" << endl;
    cout << "Output: " << sol.maximizeTheCutsSpaceOptimized(5, 5, 3, 2) << endl; 

    return 0;
}