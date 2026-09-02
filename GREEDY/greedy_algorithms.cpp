/*
 * ============================================================
 *  GREEDY ALGORITHMS — Complete Reference
 * ============================================================
 *  Greedy Principle: At each step, choose the locally optimal
 *  decision, hoping it leads to a globally optimal solution.
 *
 *  Works when: optimal substructure + greedy choice property hold.
 *  Proof technique: exchange argument or matroid theory.
 *
 *  Topics:
 *   1. Activity Selection (interval scheduling)
 *   2. Fractional Knapsack
 *   3. Job Scheduling with Deadlines
 *   4. Huffman Encoding
 *   5. Jump Game I & II — LC 55 / LC 45
 *   6. Gas Station — LC 134
 *   7. Candy Distribution — LC 135
 *   8. Minimum Number of Arrows — LC 452
 *   9. Merge Intervals — LC 56
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  1. Activity Selection Problem
//  Select max number of non-overlapping activities.
//  Greedy: always pick activity that finishes earliest.
// ─────────────────────────────────────────────────────────────
int activitySelection(vector<pair<int,int>>& activities) {
    // Sort by finish time
    sort(activities.begin(), activities.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });
    int count = 1, lastEnd = activities[0].second;
    for (int i = 1; i < (int)activities.size(); i++)
        if (activities[i].first >= lastEnd) { count++; lastEnd = activities[i].second; }
    return count;
}

// ─────────────────────────────────────────────────────────────
//  2. Fractional Knapsack
//  Take fractions of items; sort by value/weight ratio.
// ─────────────────────────────────────────────────────────────
double fractionalKnapsack(vector<pair<int,int>>& items, int W) {
    // Sort by value/weight ratio descending
    sort(items.begin(), items.end(), [](auto& a, auto& b) {
        return (double)a.first / a.second > (double)b.first / b.second;
    });
    double profit = 0;
    for (auto& [val, wt] : items) {
        if (W >= wt) { profit += val; W -= wt; }
        else          { profit += (double)val * W / wt; break; }
    }
    return profit;
}

// ─────────────────────────────────────────────────────────────
//  3. Job Scheduling with Deadlines
//  Maximise jobs done (each takes 1 unit time, has a deadline).
//  Greedy: schedule each job in the latest available slot <= deadline.
// ─────────────────────────────────────────────────────────────
int jobScheduling(vector<pair<int,int>>& jobs, int maxDeadline) {
    // Sort by profit descending
    sort(jobs.begin(), jobs.end(), [](auto& a, auto& b) { return a.first > b.first; });
    vector<int> slot(maxDeadline + 1, -1);
    int count = 0;
    for (auto& [profit, deadline] : jobs) {
        for (int t = deadline; t >= 1; t--) {
            if (slot[t] == -1) { slot[t] = profit; count++; break; }
        }
    }
    return count;
}

// ─────────────────────────────────────────────────────────────
//  4. Huffman Encoding (build Huffman tree)
// ─────────────────────────────────────────────────────────────
struct HNode {
    char ch; int freq;
    HNode *left, *right;
    HNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    bool operator>(const HNode& o) const { return freq > o.freq; }
};

void printCodes(HNode* root, string code = "") {
    if (!root) return;
    if (!root->left && !root->right) {
        cout << "   '" << root->ch << "': " << code << "\n";
        return;
    }
    printCodes(root->left,  code + "0");
    printCodes(root->right, code + "1");
}

void huffman(vector<pair<char,int>>& charFreq) {
    auto cmp = [](HNode* a, HNode* b) { return a->freq > b->freq; };
    priority_queue<HNode*, vector<HNode*>, decltype(cmp)> pq(cmp);
    for (auto& [ch, f] : charFreq) pq.push(new HNode(ch, f));
    while (pq.size() > 1) {
        HNode* l = pq.top(); pq.pop();
        HNode* r = pq.top(); pq.pop();
        HNode* parent = new HNode('\0', l->freq + r->freq);
        parent->left = l; parent->right = r;
        pq.push(parent);
    }
    printCodes(pq.top());
}

// ─────────────────────────────────────────────────────────────
//  5. Jump Game — LC 55  (can reach end?)
//     Jump Game II — LC 45 (min jumps to reach end)
// ─────────────────────────────────────────────────────────────
bool canJump(vector<int>& nums) {
    int maxReach = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (i > maxReach) return false;
        maxReach = max(maxReach, i + nums[i]);
    }
    return true;
}

int jump(vector<int>& nums) {
    int jumps = 0, curEnd = 0, farthest = 0;
    for (int i = 0; i < (int)nums.size() - 1; i++) {
        farthest = max(farthest, i + nums[i]);
        if (i == curEnd) { jumps++; curEnd = farthest; }
    }
    return jumps;
}

// ─────────────────────────────────────────────────────────────
//  6. Gas Station — LC 134
//  Can complete circular tour? Find starting station.
// ─────────────────────────────────────────────────────────────
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int totalGas = 0, curGas = 0, start = 0;
    for (int i = 0; i < (int)gas.size(); i++) {
        int net = gas[i] - cost[i];
        totalGas += net;
        curGas   += net;
        if (curGas < 0) { start = i + 1; curGas = 0; }
    }
    return totalGas >= 0 ? start : -1;
}

// ─────────────────────────────────────────────────────────────
//  7. Candy Distribution — LC 135
//  Each child gets ≥1 candy; higher rating gets more than neighbours.
// ─────────────────────────────────────────────────────────────
int candy(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> candies(n, 1);
    // Left pass
    for (int i = 1; i < n; i++)
        if (ratings[i] > ratings[i-1]) candies[i] = candies[i-1] + 1;
    // Right pass
    for (int i = n - 2; i >= 0; i--)
        if (ratings[i] > ratings[i+1]) candies[i] = max(candies[i], candies[i+1] + 1);
    return accumulate(candies.begin(), candies.end(), 0);
}

// ─────────────────────────────────────────────────────────────
//  8. Min Arrows to Burst Balloons — LC 452
//  Each balloon is a horizontal interval. Greedy: shoot at end.
// ─────────────────────────────────────────────────────────────
int findMinArrowShots(vector<vector<int>>& points) {
    sort(points.begin(), points.end(), [](auto& a, auto& b) { return a[1] < b[1]; });
    int arrows = 1, end = points[0][1];
    for (int i = 1; i < (int)points.size(); i++)
        if (points[i][0] > end) { arrows++; end = points[i][1]; }
    return arrows;
}

// ─────────────────────────────────────────────────────────────
//  9. Merge Intervals — LC 56
// ─────────────────────────────────────────────────────────────
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> res;
    for (auto& iv : intervals) {
        if (res.empty() || res.back()[1] < iv[0]) res.push_back(iv);
        else res.back()[1] = max(res.back()[1], iv[1]);
    }
    return res;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Greedy Algorithms =====\n\n";

    vector<pair<int,int>> acts = {{1,4},{3,5},{0,6},{5,7},{3,9},{5,9},{6,10},{8,11},{8,12},{2,14},{12,16}};
    cout << "1. Activity Selection: " << activitySelection(acts) << " activities\n"; // 4

    vector<pair<int,int>> items = {{60,10},{100,20},{120,30}}; // {value,weight}
    cout << "\n2. Fractional Knapsack (W=50): "
         << fractionalKnapsack(items, 50) << "\n"; // 240.0

    vector<pair<int,int>> jobs = {{20,2},{15,2},{10,1},{5,3},{1,3}}; // {profit,deadline}
    cout << "\n3. Job Scheduling: " << jobScheduling(jobs, 3) << " jobs\n"; // 3

    cout << "\n4. Huffman Codes for {a:5, b:9, c:12, d:13, e:16, f:45}:\n";
    vector<pair<char,int>> cf = {{'a',5},{'b',9},{'c',12},{'d',13},{'e',16},{'f',45}};
    huffman(cf);

    cout << "\n5. Jump Game:\n";
    vector<int> j1 = {2,3,1,1,4}, j2 = {3,2,1,0,4};
    cout << "   {2,3,1,1,4} can reach end: " << (canJump(j1)?"YES":"NO") << "\n"; // YES
    cout << "   {3,2,1,0,4} can reach end: " << (canJump(j2)?"YES":"NO") << "\n"; // NO
    cout << "   Min jumps {2,3,0,1,4}: " << jump(j1) << "\n"; // 2

    cout << "\n6. Gas Station {gas={1,2,3,4,5} cost={3,4,5,1,2}}: start at "
         << [](){ vector<int> g={1,2,3,4,5},c={3,4,5,1,2}; return canCompleteCircuit(g,c); }()
         << "\n"; // 3

    cout << "\n7. Candy {1,0,2}: " << [](){ vector<int> r={1,0,2}; return candy(r); }() << "\n"; // 5

    cout << "\n8. Min arrows {[10,16],[2,8],[1,6],[7,12]}: ";
    vector<vector<int>> bal = {{10,16},{2,8},{1,6},{7,12}};
    cout << findMinArrowShots(bal) << "\n"; // 2

    cout << "\n9. Merge intervals {[1,3],[2,6],[8,10],[15,18]}:\n   ";
    vector<vector<int>> ivs = {{1,3},{2,6},{8,10},{15,18}};
    for (auto& iv : merge(ivs)) cout << "[" << iv[0] << "," << iv[1] << "] ";
    cout << "\n"; // [1,6] [8,10] [15,18]

    return 0;
}
