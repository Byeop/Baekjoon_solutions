#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int dfsn[100010], dfse[100010], dfsl[100010], parent[100010], dfscnt;
int depth[100010];
vector<int> g[100010], child[100010];
map<pii, bool> bridge;

void dfs(int u) {
    dfsn[u] = dfsl[u] = dfscnt++;
    for (int v : g[u]) {
        if (dfsn[v] == -1) {
            parent[v] = u;
            depth[v] = depth[u] + 1;
            child[u].push_back(v);
            dfs(v);
            if (dfsl[u] < dfsl[v]) bridge[pii(u, v)] = bridge[pii(v, u)] = true;
            dfsl[u] = min(dfsl[u], dfsl[v]);
        } else if (parent[v] != u)
            dfsl[u] = min(dfsl[u], dfsl[v]);
    }
    dfse[u] = dfscnt++;
}

// is u a ancestor of v
bool isAnce(int u, int v) { return dfsn[u] <= dfsn[v] && dfse[u] >= dfse[v]; }

int findSub(int u, int v) {
    int l = 0, r = child[u].size() - 1;
    while (l != r) {
        int m = (l + r) / 2;
        int c = child[u][m];
        if (dfsn[v] > dfse[c])
            l = m + 1;
        else if (dfse[v] < dfsn[c])
            r = m - 1;
        else
            return c;
    }
    return child[u][l];
}

int main(void) {
    int n, e;
    scanf("%d %d", &n, &e);
    while (e--) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(dfsn, -1, sizeof(dfsn));
    memset(dfsl, -1, sizeof(dfsl));
    memset(depth, -1, sizeof(depth));
    depth[1] = 0;
    dfs(1);

    int q;
    scanf("%d", &q);
    while (q--) {
        int cmd;
        scanf("%d", &cmd);
        if (cmd == 1) {
            int a, b, g1, g2;
            scanf("%d %d %d %d", &a, &b, &g1, &g2);
            if (dfsn[g1] < dfsn[g2]) swap(g1, g2);
            if (depth[g1] + 1 != depth[g2])
                printf("yes\n");
            else if (!bridge[pii(g1, g2)])
                printf("yes\n");
            else if (isAnce(a, g2) == isAnce(b, g2))
                printf("yes\n");
            else
                printf("no\n");
        } else {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            if (!isAnce(c, a) && !isAnce(c, b))
                printf("yes\n");
            else if (isAnce(c, a) && isAnce(c, b)) {
                int u = findSub(c, a);
                int v = findSub(c, b);
                if (u == v)
                    printf("yes\n");
                else if (dfsl[u] < dfsn[c] && dfsl[v] < dfsn[c])
                    printf("yes\n");
                else
                    printf("no\n");
            } else {
                if (!isAnce(c, a)) swap(a, b);
                int u = findSub(c, a);
                printf("%d   ", u);
                if (dfsl[u] < dfsn[c])
                    printf("yes\n");
                else
                    printf("no\n");
            }
        }
    }

    return 0;
}