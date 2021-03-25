#include <bits/stdc++.h>

using namespace std;

int bin[4010], node[4010];

vector<int> st;
vector<int> g[4010];

const int MAX = 12;
int parent[4010][MAX], depth[4010];

void dfs(int u) {
    for (int v : g[u]) {
        if (depth[v] == -1) {
            depth[v] = depth[u] + 1;
            parent[v][0] = u;
            dfs(v);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; diff; ++i) {
        if (diff & 1) u = parent[u][i];
        diff >>= 1;
    }
    if (u != v) {
        for (int k = MAX - 1; k >= 0; --k) {
            if (parent[u][k] != -1 && parent[u][k] != parent[v][k]) {
                u = parent[u][k];
                v = parent[v][k];
            }
        }
        u = parent[u][0];
    }
    return u;
}

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n * 2; ++i) scanf("%1d", bin + i);
    int x, y;
    scanf("%d %d", &x, &y);

    int t = 1;
    st.push_back(t++);
    node[1] = 1;
    for (int i = 2; i <= n * 2; ++i) {
        if (bin[i] == 0) {
            node[i] = t;
            g[st.back()].push_back(t);
            st.push_back(t++);
        } else {
            node[i] = st.back();
            st.pop_back();
        }
    }

    memset(parent, -1, sizeof(parent));
    memset(depth, -1, sizeof(depth));
    depth[1] = 1;
    dfs(1);
    for (int k = 0; k < MAX - 1; ++k)
        for (int i = 1; i <= n; ++i)
            if (parent[i][k] != -1) parent[i][k + 1] = parent[parent[i][k]][k];

    x = node[x], y = node[y];
    int z = lca(x, y);
    for (int i = 1; i <= n * 2; ++i)
        if (node[i] == z) printf("%d ", i);

    return 0;
}