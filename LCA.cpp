#include <bits/stdc++.h>
using namespace std;

struct BinaryLift {
    int n, LOG;
    vector<int> depth;
    vector<vector<int>> up, g;

    BinaryLift(int N) : n(N) {
        LOG = 1; while ((1 << LOG) <= n) ++LOG;
        g.assign(n + 1, {});
        up.assign(LOG, vector<int>(n + 1));
        depth.assign(n + 1, 0);
    }
    void add_edge(int u, int v) { g[u].push_back(v); g[v].push_back(u); }
    void build(int root = 1) { dfs(root, root); }
    int lift(int v, int k) const {
        for (int i = 0; i < LOG && v; ++i) if (k >> i & 1) v = up[i][v];
        return v;
    }
private:
    void dfs(int v, int p) {
        up[0][v] = p;
        for (int i = 1; i < LOG; ++i) up[i][v] = up[i - 1][ up[i - 1][v] ];
        for (int to : g[v]) if (to != p) {
            depth[to] = depth[v] + 1;
            dfs(to, v);
        }
    }
};

struct LCA {
    BinaryLift bl;
    LCA(int N) : bl(N) {}
    void add_edge(int u, int v) { bl.add_edge(u, v); }
    void build(int root = 1) { bl.build(root); }
    int query(int u, int v) {
        if (bl.depth[u] < bl.depth[v]) swap(u, v);
        u = bl.lift(u, bl.depth[u] - bl.depth[v]);
        if (u == v) return u;
        for (int i = bl.LOG - 1; i >= 0; --i)
            if (bl.up[i][u] != bl.up[i][v])
                u = bl.up[i][u], v = bl.up[i][v];
        return bl.up[0][u];
    }
};
