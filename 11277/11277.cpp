#include <bits/stdc++.h>

using namespace std;

vector<int> g[50];
int n, m;

int getNode(int x) {
    if (x < 0)
        return -x + n;
    else
        return x;
}

vector<int> st;
int dfs_num[50], visited[50], dfs_cnt = 1, sccn[50], sn;
int scc(int u) {
    st.push_back(u);
    visited[u] = 1;
    int ret = dfs_num[u] = dfs_cnt++;
    for (int v : g[u]) {
        if (!visited[v])
            ret = min(ret, scc(v));
        else if (visited[v] != -1)
            ret = min(ret, dfs_num[v]);
    }
    if (ret == dfs_num[u]) {
        while (1) {
            int t = st.back();
            st.pop_back();
            sccn[t] = sn;
            visited[t] = -1;
            if (t == u) break;
        }
        sn++;
    }
    return ret;
}

int main(void) {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        g[getNode(-a)].push_back(getNode(b));
        g[getNode(-b)].push_back(getNode(a));
    }

    for (int i = 1; i <= 2 * n; ++i)
        if (!dfs_num[i]) scc(i);
    for (int i = 1; i <= n; ++i) {
        if (sccn[i] == sccn[i + n]) {
            printf("0");
            return 0;
        }
    }
    printf("1");

    return 0;
}