/*
 * ============================================================
 *  HEAPS — Complete Reference
 * ============================================================
 *  A Heap is a complete binary tree stored as an array.
 *  Max-Heap: parent >= children   Min-Heap: parent <= children
 *
 *  Index relationships (0-based):
 *    parent(i)  = (i-1)/2
 *    left(i)    = 2*i+1
 *    right(i)   = 2*i+2
 *
 *  Topics:
 *   1. Min-Heap & Max-Heap implementation from scratch
 *   2. Heap Sort
 *   3. Kth Largest/Smallest Element — LC 215 / LC 703
 *   4. Top K Frequent Elements — LC 347
 *   5. Merge K Sorted Lists — LC 23
 *   6. Median from Data Stream — LC 295
 *   7. Task Scheduler — LC 621
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  1. Min-Heap from scratch
// ─────────────────────────────────────────────────────────────
class MinHeap {
    vector<int> heap;

    void siftUp(int i) {
        while (i > 0 && heap[(i-1)/2] > heap[i]) {
            swap(heap[(i-1)/2], heap[i]);
            i = (i-1)/2;
        }
    }

    void siftDown(int i) {
        int n = heap.size();
        while (2*i+1 < n) {
            int smallest = i, l = 2*i+1, r = 2*i+2;
            if (l < n && heap[l] < heap[smallest]) smallest = l;
            if (r < n && heap[r] < heap[smallest]) smallest = r;
            if (smallest == i) break;
            swap(heap[i], heap[smallest]);
            i = smallest;
        }
    }

public:
    void push(int val) { heap.push_back(val); siftUp(heap.size()-1); }

    int  top()  { return heap[0]; }
    bool empty(){ return heap.empty(); }
    int  size() { return heap.size(); }

    void pop() {
        heap[0] = heap.back(); heap.pop_back();
        if (!heap.empty()) siftDown(0);
    }

    // Build heap from array in O(n)
    void buildHeap(vector<int>& arr) {
        heap = arr;
        for (int i = heap.size()/2 - 1; i >= 0; i--)
            siftDown(i);
    }
};

// ─────────────────────────────────────────────────────────────
//  2. Kth Largest Element — LC 215
//  Use min-heap of size k: maintain top-k elements
// ─────────────────────────────────────────────────────────────
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minPQ; // min-heap
    for (int x : nums) {
        minPQ.push(x);
        if ((int)minPQ.size() > k) minPQ.pop();
    }
    return minPQ.top();
}

// ─────────────────────────────────────────────────────────────
//  3. Top K Frequent Elements — LC 347
// ─────────────────────────────────────────────────────────────
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int,int> freq;
    for (int x : nums) freq[x]++;

    // Min-heap by frequency
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    for (auto& [val, cnt] : freq) {
        pq.push({cnt, val});
        if ((int)pq.size() > k) pq.pop();
    }

    vector<int> res;
    while (!pq.empty()) { res.push_back(pq.top().second); pq.pop(); }
    return res;
}

// ─────────────────────────────────────────────────────────────
//  4. Merge K Sorted Lists — LC 23
// ─────────────────────────────────────────────────────────────
struct ListNode { int val; ListNode* next; ListNode(int v) : val(v), next(nullptr) {} };

ListNode* mergeKLists(vector<ListNode*>& lists) {
    using T = pair<int, ListNode*>;
    priority_queue<T, vector<T>, greater<T>> pq; // min-heap by value

    for (auto node : lists)
        if (node) pq.push({node->val, node});

    ListNode dummy(0); ListNode* cur = &dummy;
    while (!pq.empty()) {
        auto [val, node] = pq.top(); pq.pop();
        cur->next = node; cur = cur->next;
        if (node->next) pq.push({node->next->val, node->next});
    }
    return dummy.next;
}

// ─────────────────────────────────────────────────────────────
//  5. Median from Data Stream — LC 295
//  Two heaps: max-heap for lower half, min-heap for upper half
// ─────────────────────────────────────────────────────────────
class MedianFinder {
    priority_queue<int>                          maxH; // lower half
    priority_queue<int, vector<int>, greater<int>> minH; // upper half

public:
    void addNum(int num) {
        maxH.push(num);
        minH.push(maxH.top()); maxH.pop();
        if (minH.size() > maxH.size() + 1) {
            maxH.push(minH.top()); minH.pop();
        }
    }

    double findMedian() {
        if (minH.size() == maxH.size())
            return (maxH.top() + minH.top()) / 2.0;
        return minH.top();
    }
};

// ─────────────────────────────────────────────────────────────
//  6. Task Scheduler — LC 621
//  Greedy: always process most frequent remaining task
// ─────────────────────────────────────────────────────────────
int leastInterval(vector<char>& tasks, int n) {
    vector<int> freq(26, 0);
    for (char t : tasks) freq[t - 'A']++;

    priority_queue<int> maxH(freq.begin(), freq.end());
    int time = 0;

    while (!maxH.empty()) {
        vector<int> temp;
        int cycles = n + 1;
        while (cycles > 0 && !maxH.empty()) {
            temp.push_back(maxH.top() - 1); maxH.pop(); cycles--;
        }
        for (int t : temp) if (t > 0) maxH.push(t);
        time += maxH.empty() ? (n + 1 - cycles) : (n + 1);
    }
    return time;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Heaps =====\n\n";

    // 1. Custom MinHeap
    cout << "1. Custom Min-Heap:\n";
    MinHeap mh;
    for (int x : {5, 3, 8, 1, 4, 9, 2}) mh.push(x);
    cout << "   Extracting in order: ";
    while (!mh.empty()) { cout << mh.top() << " "; mh.pop(); }
    cout << "\n";

    // Build heap
    vector<int> arr = {4, 10, 3, 5, 1};
    mh.buildHeap(arr);
    cout << "   Build heap {4,10,3,5,1}, top: " << mh.top() << "\n"; // 1

    // 2. Kth Largest
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    cout << "\n2. 2nd largest in {3,2,1,5,6,4}: "
         << findKthLargest(nums, 2) << "\n"; // 5

    // 3. Top K Frequent
    vector<int> freq = {1, 1, 1, 2, 2, 3};
    auto topK = topKFrequent(freq, 2);
    cout << "\n3. Top 2 frequent in {1,1,1,2,2,3}: ";
    for (int x : topK) cout << x << " ";
    cout << "\n"; // 1 2

    // 4. Merge K sorted lists
    auto makeList = [](vector<int> v) {
        ListNode* head = nullptr;
        for (int i = v.size() - 1; i >= 0; i--)
            head = new ListNode(v[i]), head->next = (i < (int)v.size()-1 ? head->next : nullptr);
        // Fix: build properly
        ListNode dummy(0); ListNode* cur = &dummy;
        for (int x : v) { cur->next = new ListNode(x); cur = cur->next; }
        return dummy.next;
    };
    vector<ListNode*> lists = {makeList({1,4,5}), makeList({1,3,4}), makeList({2,6})};
    cout << "\n4. Merge K sorted lists:\n   ";
    ListNode* merged = mergeKLists(lists);
    while (merged) { cout << merged->val << " "; merged = merged->next; }
    cout << "\n"; // 1 1 2 3 4 4 5 6

    // 5. Median finder
    cout << "\n5. Median from stream:\n";
    MedianFinder mf;
    for (int x : {1, 2, 3, 4, 5}) {
        mf.addNum(x);
        cout << "   After adding " << x << ": median = " << mf.findMedian() << "\n";
    }

    // 6. Task Scheduler
    vector<char> tasks = {'A','A','A','B','B','B'};
    cout << "\n6. Task scheduler (n=2): " << leastInterval(tasks, 2) << "\n"; // 8

    return 0;
}
