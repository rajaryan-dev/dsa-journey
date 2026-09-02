/*
 * ============================================================
 *  DISJOINT SET UNION (Union-Find) — DSU
 * ============================================================
 *  Operations:
 *   - find(x)     : returns root/representative of x's component
 *   - unite(x, y) : merges component of x and component of y
 *
 *  Optimisations:
 *   - Path Compression : flatten tree during find()
 *   - Union by Rank    : attach smaller tree under larger
 *   Combined → near O(α(n)) ≈ O(1) amortised per operation
 *
 *  Applications:
 *   - Cycle detection in undirected graphs
 *   - Kruskal's MST
 *   - Connected components
 *   - Number of islands (dynamic)
 *   - Redundant connection — LC 684
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  DSU Class — complete implementation
// ─────────────────────────────────────────────────────────────
class DSU {
public:
    vector<int> parent, rank_, size_;
    int components;

    DSU(int n) : parent(n), rank_(n, 0), size_(n, 1), components(n) {
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
    }

    // Find with path compression
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // recursive path compression
        return parent[x];
    }

    // Union by rank — returns true if merged (were in different components)
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false; // already in same component

        if (rank_[rx] < rank_[ry]) swap(rx, ry);
        parent[ry] = rx;
        size_[rx] += size_[ry];
        if (rank_[rx] == rank_[ry]) rank_[rx]++;
        components--;
        return true;
    }

    bool connected(int x, int y) { return find(x) == find(y); }
    int  getSize(int x)          { return size_[find(x)]; }
    int  numComponents()         { return components; }
};

// ─────────────────────────────────────────────────────────────
//  Application 1: Number of Connected Components — LC 323
// ─────────────────────────────────────────────────────────────
int countComponents(int n, vector<vector<int>>& edges) {
    DSU dsu(n);
    for (auto& e : edges) dsu.unite(e[0], e[1]);
    return dsu.numComponents();
}

// ─────────────────────────────────────────────────────────────
//  Application 2: Redundant Connection — LC 684
//  Find the edge that forms a cycle (return it)
// ─────────────────────────────────────────────────────────────
vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    DSU dsu(n + 1); // nodes 1..n
    for (auto& e : edges) {
        if (!dsu.unite(e[0], e[1])) return e; // cycle detected
    }
    return {};
}

// ─────────────────────────────────────────────────────────────
//  Application 3: Number of Islands II (Dynamic) — LC 305
//  Add one land cell at a time, count islands after each add
// ─────────────────────────────────────────────────────────────
vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
    DSU dsu(m * n);
    vector<bool> land(m * n, false);
    vector<int> result;
    int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    int islands = 0;

    for (auto& pos : positions) {
        int r = pos[0], c = pos[1];
        int id = r * n + c;
        if (!land[id]) {
            land[id] = true;
            islands++;
            for (auto& d : dirs) {
                int nr = r + d[0], nc = c + d[1];
                int nid = nr * n + nc;
                if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
                    land[nid] && dsu.unite(id, nid))
                    islands--;
            }
        }
        result.push_back(islands);
    }
    return result;
}

// ─────────────────────────────────────────────────────────────
//  Application 4: Accounts Merge — LC 721
//  Merge accounts sharing the same email
// ─────────────────────────────────────────────────────────────
vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    int n = accounts.size();
    DSU dsu(n);
    unordered_map<string, int> emailToAcc;

    for (int i = 0; i < n; i++)
        for (int j = 1; j < (int)accounts[i].size(); j++) {
            string& email = accounts[i][j];
            if (emailToAcc.count(email))
                dsu.unite(i, emailToAcc[email]);
            else
                emailToAcc[email] = i;
        }

    unordered_map<int, vector<string>> merged;
    for (auto& [email, idx] : emailToAcc)
        merged[dsu.find(idx)].push_back(email);

    vector<vector<string>> result;
    for (auto& [idx, emails] : merged) {
        sort(emails.begin(), emails.end());
        emails.insert(emails.begin(), accounts[idx][0]);
        result.push_back(emails);
    }
    return result;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Disjoint Set Union (Union-Find) =====\n\n";

    // Basic DSU demo
    DSU dsu(6); // nodes 0..5
    cout << "Nodes: 0,1,2,3,4,5  (6 components initially)\n";
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    cout << "After unite(0,1), unite(1,2), unite(3,4):\n";
    cout << "  Components: " << dsu.numComponents() << "\n"; // 3
    cout << "  connected(0,2): " << (dsu.connected(0,2) ? "YES":"NO") << "\n"; // YES
    cout << "  connected(0,3): " << (dsu.connected(0,3) ? "YES":"NO") << "\n"; // NO
    cout << "  size of 0's component: " << dsu.getSize(0) << "\n"; // 3

    // Number of components
    vector<vector<int>> edges = {{0,1},{1,2},{3,4}};
    cout << "\nNumber of components (5 nodes, edges{0-1,1-2,3-4}): "
         << countComponents(5, edges) << "\n"; // 2

    // Redundant connection
    vector<vector<int>> re = {{1,2},{1,3},{2,3}};
    auto red = findRedundantConnection(re);
    cout << "\nRedundant edge: [" << red[0] << "," << red[1] << "]\n"; // [2,3]

    // Number of islands II
    vector<vector<int>> positions = {{0,0},{0,1},{1,2},{2,1}};
    auto islands = numIslands2(3, 3, positions);
    cout << "\nNumber of islands after each add: ";
    for (int x : islands) cout << x << " ";
    cout << "\n"; // 1 1 2 3

    return 0;
}
