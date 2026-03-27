/**
 * ============================================================
 * std::priority_queue — Complete Guide (C++ STL)
 * ============================================================
 *
 * A Priority Queue is a container adapter that provides
 * constant-time lookup of the highest-priority element.
 *
 * ┌─────────────────────────────────────────────────┐
 * │  Key Complexities                               │
 * │  ─────────────────                              │
 * │  push / emplace  →  O(log N)                    │
 * │  pop             →  O(log N)                    │
 * │  top             →  O(1)                        │
 * │  size / empty    →  O(1)                        │
 * └─────────────────────────────────────────────────┘
 *
 * Internal Structure:
 *   • Default behaviour  →  MAX HEAP (largest element on top)
 *   • Underlying container → std::vector (by default)
 *   • Heap property is maintained using std::make_heap,
 *     std::push_heap, std::pop_heap internally.
 *
 * Full template signature:
 *   priority_queue<Type, Container, Comparator>
 *
 * Sections covered in this file:
 *   1. Max Heap (default)
 *   2. Removal
 *   3. Min Heap (std::greater)
 *   4. Utility functions (size, empty, swap)
 *   5. Building a PQ from an existing vector
 *   6. Priority Queue with pairs
 *   7. Custom comparator for structs (operator overload)
 *   8. Custom comparator using lambda
 *   9. Practical problem — K-th largest element
 */

#include <iostream>
#include <queue>
#include <vector>
#include <functional> // std::greater
#include <string>
#include <algorithm>  // std::sort (used in K-th largest demo)

using namespace std;

// ─── Helper: print & empty a COPY of a priority_queue ───
template <typename T>
void printPQ(T pq, const string& name) {
    cout << name << ": [Top->Tail] ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}

// ─── Task struct and comparator (defined outside main for template compat) ───
struct Task {
    string name;
    int priority;    // higher number = higher priority
    int deadline;    // lower number  = earlier deadline
};

// Custom comparator: sort by priority DESC, then deadline ASC
// NOTE: In a priority_queue the comparator works OPPOSITE to sort.
//       Return true if 'a' should come AFTER 'b' (i.e., b has higher priority).
struct TaskComparator {
    bool operator()(const Task& a, const Task& b) const {
        if (a.priority != b.priority)
            return a.priority < b.priority;  // higher priority on top
        return a.deadline > b.deadline;       // earlier deadline wins tie
    }
};

int main() {

    // ====================================================
    // 1. Max Heap (Default Behaviour)
    // ====================================================
    cout << "=== 1. Max Heap (Default) ===" << endl;

    // Declaration: priority_queue<Type>
    // The largest element is always at the top.
    // Think of it like a stack, but the "top" is decided
    // by VALUE (priority), NOT by insertion order.
    priority_queue<int> maxPQ;

    // push / emplace — O(log N)
    maxPQ.push(5);
    maxPQ.push(2);
    maxPQ.push(10);
    maxPQ.emplace(8);   // emplace constructs in-place (slightly more efficient for complex types)

    // After all inserts the internal heap looks roughly like:
    //        10
    //       /  \
    //      8    5
    //     /
    //    2

    // top() — O(1) — returns the largest element
    cout << "Top element (Max): " << maxPQ.top() << endl; // 10

    printPQ(maxPQ, "Max Heap");  // 10 8 5 2


    // ====================================================
    // 2. Removal (pop)
    // ====================================================
    cout << "\n=== 2. Removal from Max Heap ===" << endl;

    // pop() — O(log N) — removes the top (largest) element
    maxPQ.pop(); // removes 10
    cout << "After pop(), new Top: " << maxPQ.top() << endl; // 8

    maxPQ.pop(); // removes 8
    maxPQ.pop(); // removes 5
    cout << "After 3 pops, Top: " << maxPQ.top() << endl;   // 2
    cout << "Size now: " << maxPQ.size() << endl;            // 1


    // ====================================================
    // 3. Min Heap (using std::greater)
    // ====================================================
    cout << "\n=== 3. Min Heap ===" << endl;

    // Syntax: priority_queue<Type, Container, Comparator>
    //   • vector<int>    → underlying container
    //   • greater<int>   → reverses comparison so SMALLEST is on top
    priority_queue<int, vector<int>, greater<int>> minPQ;

    minPQ.push(5);
    minPQ.push(2);
    minPQ.push(10);
    minPQ.push(8);

    cout << "Top element (Min): " << minPQ.top() << endl; // 2

    printPQ(minPQ, "Min Heap");  // 2 5 8 10


    // ====================================================
    // 4. Utility Functions
    // ====================================================
    cout << "\n=== 4. Utility Functions ===" << endl;

    // size()  — O(1) — number of elements
    cout << "Size of Min Heap: " << minPQ.size() << endl;

    // empty() — O(1) — check if PQ is empty
    cout << "Is Min Heap empty? " << (minPQ.empty() ? "Yes" : "No") << endl;

    // swap() — O(1) — swap contents of two PQs of the same type
    priority_queue<int, vector<int>, greater<int>> otherMinPQ;
    otherMinPQ.push(100);
    otherMinPQ.push(200);

    minPQ.swap(otherMinPQ);
    cout << "After swap → minPQ top: " << minPQ.top();              // 100
    cout << ", otherMinPQ top: " << otherMinPQ.top() << endl;       // 2


    // ====================================================
    // 5. Building a PQ from an Existing Vector
    // ====================================================
    cout << "\n=== 5. Build PQ from Vector ===" << endl;

    // You can construct a PQ directly from iterators.
    // This internally calls std::make_heap → O(N) time.
    vector<int> nums = {40, 10, 30, 20, 50};

    // Max Heap from vector
    priority_queue<int> pqFromVec(nums.begin(), nums.end());
    printPQ(pqFromVec, "PQ from vector (Max)");  // 50 40 30 20 10

    // Min Heap from vector
    priority_queue<int, vector<int>, greater<int>>
        minPQFromVec(nums.begin(), nums.end());
    printPQ(minPQFromVec, "PQ from vector (Min)");  // 10 20 30 40 50


    // ====================================================
    // 6. Priority Queue with Pairs
    // ====================================================
    cout << "\n=== 6. PQ with Pairs ===" << endl;

    // Pairs are compared LEXICOGRAPHICALLY:
    //   first by pair.first, then by pair.second.
    // So in a Max PQ, the pair with the LARGEST .first comes first.
    // This is very useful in algorithms like Dijkstra's.
    priority_queue<pair<int, string>> pairPQ;

    pairPQ.push({3, "Low"});
    pairPQ.push({1, "Very Low"});
    pairPQ.push({10, "High"});
    pairPQ.push({5, "Medium"});

    cout << "Pair PQ (by priority):" << endl;
    while (!pairPQ.empty()) {
        auto top = pairPQ.top();
        cout << "  Priority " << top.first << " -> " << top.second << endl;
        pairPQ.pop();
    }
    // Output order: High(10), Medium(5), Low(3), Very Low(1)


    // ====================================================
    // 7. Custom Comparator for Structs
    // ====================================================
    cout << "\n=== 7. Custom Struct Comparator ===" << endl;

    // Task struct and TaskComparator are defined above main().
    // See lines above for the struct definitions and comparator logic.

    priority_queue<Task, vector<Task>, TaskComparator> taskPQ;

    taskPQ.push({"Bug fix",       5, 2});
    taskPQ.push({"New feature",   3, 1});
    taskPQ.push({"Code review",   5, 1});  // same priority as Bug fix, earlier deadline
    taskPQ.push({"Documentation", 1, 5});

    cout << "Task Queue (highest priority first):" << endl;
    while (!taskPQ.empty()) {
        const Task& t = taskPQ.top();
        cout << "  [P:" << t.priority << " D:" << t.deadline << "] " << t.name << endl;
        taskPQ.pop();
    }
    // Expected:
    //   [P:5 D:1] Code review     ← same P as Bug fix, but earlier deadline
    //   [P:5 D:2] Bug fix
    //   [P:3 D:1] New feature
    //   [P:1 D:5] Documentation


    // ====================================================
    // 8. Lambda Comparator (C++11 / C++20)
    // ====================================================
    cout << "\n=== 8. Lambda Comparator ===" << endl;

    // You can also pass a lambda as a comparator.
    // Useful for quick, one-off comparisons without writing a struct.
    auto cmp = [](int a, int b) {
        // Compare by absolute value → smallest absolute value on top
        return abs(a) > abs(b);
    };

    // Need to pass the lambda type using decltype and the lambda itself to the constructor
    priority_queue<int, vector<int>, decltype(cmp)> absPQ(cmp);

    absPQ.push(-10);
    absPQ.push(3);
    absPQ.push(-1);
    absPQ.push(7);

    cout << "Min Heap by absolute value:" << endl;
    while (!absPQ.empty()) {
        cout << "  " << absPQ.top() << endl;
        absPQ.pop();
    }
    // Expected: -1, 3, 7, -10  (sorted by |value|: 1 < 3 < 7 < 10)


    // ====================================================
    // 9. Practical Example — K-th Largest Element
    // ====================================================
    cout << "\n=== 9. K-th Largest Element ===" << endl;

    // Problem: Given an array, find the K-th largest element.
    // Strategy: Use a MIN HEAP of size K.
    //   • Push elements into the heap.
    //   • If heap size exceeds K, pop the smallest.
    //   • After processing all elements, the top of the heap = K-th largest.
    // Time: O(N log K)  |  Space: O(K)

    vector<int> arr = {7, 10, 4, 3, 20, 15};
    int k = 3;

    priority_queue<int, vector<int>, greater<int>> kHeap; // min heap

    for (int val : arr) {
        kHeap.push(val);
        if ((int)kHeap.size() > k) {
            kHeap.pop(); // remove the smallest → only K largest remain
        }
    }

    cout << "Array: ";
    for (int v : arr) cout << v << " ";
    cout << endl;

    // Verify by sorting a copy
    vector<int> sorted_arr = arr;
    sort(sorted_arr.rbegin(), sorted_arr.rend()); // descending
    cout << "Sorted (desc): ";
    for (int v : sorted_arr) cout << v << " ";
    cout << endl;

    cout << k << "-th largest element: " << kHeap.top() << endl;
    // arr sorted desc = {20, 15, 10, 7, 4, 3}  →  3rd largest = 10


    // ====================================================
    // Quick Reference Cheat Sheet (for revision)
    // ====================================================
    /*
    ┌──────────────────────────────────────────────────────────────┐
    │  MAX HEAP:  priority_queue<int> pq;                         │
    │  MIN HEAP:  priority_queue<int, vector<int>, greater<int>>  │
    │                                                              │
    │  pq.push(x)   / pq.emplace(x)  → Insert       O(log N)    │
    │  pq.pop()                       → Remove top    O(log N)    │
    │  pq.top()                       → Peek top      O(1)       │
    │  pq.size()                      → Count          O(1)       │
    │  pq.empty()                     → Is empty?      O(1)       │
    │  pq.swap(other)                 → Swap contents  O(1)       │
    │                                                              │
    │  Build from vector: O(N)                                     │
    │  priority_queue<int> pq(vec.begin(), vec.end());            │
    │                                                              │
    │  Custom comparator (struct with operator()):                 │
    │  priority_queue<T, vector<T>, Comparator> pq;               │
    │                                                              │
    │  Lambda comparator:                                          │
    │  auto cmp = [](T a, T b){ return ... ; };                   │
    │  priority_queue<T, vector<T>, decltype(cmp)> pq(cmp);       │
    └──────────────────────────────────────────────────────────────┘
    */

    return 0;
}