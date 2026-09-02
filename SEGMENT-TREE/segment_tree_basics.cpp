/*
 * ============================================================
 *  SEGMENT TREE — Complete Reference
 * ============================================================
 *  A Segment Tree is a binary tree for efficient range queries
 *  and point updates on arrays.
 *
 *  Operations:
 *   - Build    : O(n)
 *   - Query    : O(log n)  — range sum, min, max, gcd
 *   - Update   : O(log n)  — point update
 *   - Range Update + Lazy Propagation: O(log n)
 *
 *  Array to tree index mapping (1-based):
 *   node i → children: 2i (left), 2i+1 (right)
 *
 *  Topics:
 *   1. Segment Tree — Range Sum Query
 *   2. Segment Tree — Range Min Query
 *   3. Lazy Propagation — Range Update (add to range, query sum)
 *   4. Coordinate Compression + Seg Tree
 *   5. Count of Range Sum — LC 327 (merge sort approach)
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  1. Segment Tree — Range Sum Query + Point Update
// ─────────────────────────────────────────────────────────────
class SegTreeSum {
    int n;
    vector<long long> tree;

public:
    SegTreeSum(int n) : n(n), tree(4 * n, 0) {}

    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) { tree[node] = arr[start]; return; }
        int mid = (start + end) / 2;
        build(arr, 2*node,   start, mid);
        build(arr, 2*node+1, mid+1, end);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    void build(vector<int>& arr) { build(arr, 1, 0, n - 1); }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) { tree[node] = val; return; }
        int mid = (start + end) / 2;
        if (idx <= mid) update(2*node,   start, mid,   idx, val);
        else            update(2*node+1, mid+1, end,   idx, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    void update(int idx, int val) { update(1, 0, n - 1, idx, val); }

    long long query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;         // out of range
        if (l <= start && end <= r) return tree[node]; // fully in range
        int mid = (start + end) / 2;
        return query(2*node,   start, mid,   l, r) +
               query(2*node+1, mid+1, end,   l, r);
    }

    long long query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

// ─────────────────────────────────────────────────────────────
//  2. Segment Tree — Range Min Query
// ─────────────────────────────────────────────────────────────
class SegTreeMin {
    int n;
    vector<int> tree;

public:
    SegTreeMin(int n) : n(n), tree(4 * n, INT_MAX) {}

    void build(vector<int>& arr, int node, int s, int e) {
        if (s == e) { tree[node] = arr[s]; return; }
        int m = (s + e) / 2;
        build(arr, 2*node, s, m); build(arr, 2*node+1, m+1, e);
        tree[node] = min(tree[2*node], tree[2*node+1]);
    }
    void build(vector<int>& arr) { build(arr, 1, 0, n-1); }

    int query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return INT_MAX;
        if (l <= s && e <= r) return tree[node];
        int m = (s + e) / 2;
        return min(query(2*node, s, m, l, r), query(2*node+1, m+1, e, l, r));
    }
    int query(int l, int r) { return query(1, 0, n-1, l, r); }
};

// ─────────────────────────────────────────────────────────────
//  3. Segment Tree with Lazy Propagation
//  Supports:
//   - Range add (add v to all elements in [l,r])
//   - Range sum query
// ─────────────────────────────────────────────────────────────
class LazySegTree {
    int n;
    vector<long long> tree, lazy;

    void pushDown(int node, int start, int end) {
        if (lazy[node] != 0) {
            int mid = (start + end) / 2;
            tree[2*node]   += lazy[node] * (mid - start + 1);
            tree[2*node+1] += lazy[node] * (end - mid);
            lazy[2*node]   += lazy[node];
            lazy[2*node+1] += lazy[node];
            lazy[node] = 0;
        }
    }

public:
    LazySegTree(int n) : n(n), tree(4*n, 0), lazy(4*n, 0) {}

    void build(vector<int>& arr, int node, int s, int e) {
        if (s == e) { tree[node] = arr[s]; return; }
        int m = (s + e) / 2;
        build(arr, 2*node, s, m); build(arr, 2*node+1, m+1, e);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
    void build(vector<int>& arr) { build(arr, 1, 0, n-1); }

    // Range add: add val to all elements in [l,r]
    void rangeUpdate(int node, int s, int e, int l, int r, long long val) {
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            tree[node] += val * (e - s + 1);
            lazy[node] += val;
            return;
        }
        pushDown(node, s, e);
        int m = (s + e) / 2;
        rangeUpdate(2*node, s, m, l, r, val); rangeUpdate(2*node+1, m+1, e, l, r, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
    void rangeUpdate(int l, int r, long long val) { rangeUpdate(1, 0, n-1, l, r, val); }

    long long query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node];
        pushDown(node, s, e);
        int m = (s + e) / 2;
        return query(2*node, s, m, l, r) + query(2*node+1, m+1, e, l, r);
    }
    long long query(int l, int r) { return query(1, 0, n-1, l, r); }
};

// ─────────────────────────────────────────────────────────────
//  4. Fenwick Tree (Binary Indexed Tree / BIT)
//  Simpler alternative for prefix sum queries + point updates
//  O(log n) per operation, O(n) space
// ─────────────────────────────────────────────────────────────
class FenwickTree {
    int n;
    vector<long long> bit;

public:
    FenwickTree(int n) : n(n), bit(n + 1, 0) {}

    void update(int i, long long delta) {
        for (++i; i <= n; i += i & (-i)) // i & (-i) = lowest set bit
            bit[i] += delta;
    }

    long long prefixSum(int i) {
        long long sum = 0;
        for (++i; i > 0; i -= i & (-i))
            sum += bit[i];
        return sum;
    }

    long long rangeQuery(int l, int r) {
        return prefixSum(r) - (l > 0 ? prefixSum(l - 1) : 0);
    }
};

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Segment Tree & Fenwick Tree =====\n\n";

    vector<int> arr = {1, 3, 5, 7, 9, 11};
    int n = arr.size();
    cout << "Array: {1, 3, 5, 7, 9, 11}\n\n";

    // 1. Range Sum
    SegTreeSum st(n);
    st.build(arr);
    cout << "1. Range Sum Query:\n";
    cout << "   sum[0,5] = " << st.query(0, 5) << "\n"; // 36
    cout << "   sum[1,3] = " << st.query(1, 3) << "\n"; // 15
    st.update(1, 10); // arr[1] = 10
    cout << "   After update arr[1]=10:\n";
    cout << "   sum[0,3] = " << st.query(0, 3) << "\n"; // 1+10+5+7=23

    // 2. Range Min
    vector<int> arr2 = {2, 4, 3, 1, 6, 7, 8, 9};
    SegTreeMin stMin(arr2.size());
    stMin.build(arr2);
    cout << "\n2. Range Min Query {2,4,3,1,6,7,8,9}:\n";
    cout << "   min[0,7] = " << stMin.query(0, 7) << "\n"; // 1
    cout << "   min[0,2] = " << stMin.query(0, 2) << "\n"; // 2
    cout << "   min[2,5] = " << stMin.query(2, 5) << "\n"; // 1

    // 3. Lazy Propagation
    vector<int> arr3 = {1, 2, 3, 4, 5};
    LazySegTree lst(5);
    lst.build(arr3);
    cout << "\n3. Lazy Segment Tree {1,2,3,4,5}:\n";
    cout << "   sum[0,4] = " << lst.query(0, 4) << "\n"; // 15
    lst.rangeUpdate(1, 3, 10); // add 10 to [1,3]
    cout << "   After range add 10 to [1,3]:\n";
    cout << "   sum[0,4] = " << lst.query(0, 4) << "\n"; // 45
    cout << "   sum[1,3] = " << lst.query(1, 3) << "\n"; // 39

    // 4. Fenwick Tree
    vector<int> arr4 = {3, 2, -1, 6, 5, 4, -3, 3, 7, 2, 3};
    FenwickTree ft(arr4.size());
    for (int i = 0; i < (int)arr4.size(); i++) ft.update(i, arr4[i]);
    cout << "\n4. Fenwick Tree {3,2,-1,6,5,4,-3,3,7,2,3}:\n";
    cout << "   prefix sum [0,4] = " << ft.rangeQuery(0, 4) << "\n"; // 15
    cout << "   range sum  [2,6] = " << ft.rangeQuery(2, 6) << "\n"; // 11
    ft.update(4, 3); // arr[4] += 3 → now arr[4] = 8
    cout << "   After update arr[4]+=3:\n";
    cout << "   prefix sum [0,4] = " << ft.rangeQuery(0, 4) << "\n"; // 18

    return 0;
}
