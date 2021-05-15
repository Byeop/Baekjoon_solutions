#include <bits/stdc++.h>

using namespace std;

vector<int> g[10000], g2[10000], st;
int dfsn[10000], dfscnt, finished[10000], scc[10000], sccn;
long long score[10000], ind[10000], visited[10000];

map<string, int> msi;

int dfs(int u) {
    int ret = dfsn[u] = dfscnt++;
    st.push_back(u);
    for (int v : g[u]) {
        if (dfsn[v] == -1)
            ret = min(ret, dfs(v));
        else if (!finished[v])
            ret = min(ret, dfsn[v]);
    }

    if (ret == dfsn[u]) {
        while (1) {
            int t = st.back();
            st.pop_back();
            finished[t] = true;
            scc[t] = sccn;
            if (t == u) break;
        }
        sccn++;
    }

    return ret;
}

void dfs2(int u) {
    visited[u] = 1;
    for (int v : g[u]) {
        if (!visited[v]) dfs2(v);
        if (scc[u] != scc[v]) {
            g2[u].push_back(v);
            ind[v]++;
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, cnt = 1;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string u, v;
        int t;
        cin >> v >> t;
        if (msi[v] == 0) msi[v] = cnt++;
        while (t--) {
            cin >> u;
            if (msi[u] == 0) msi[u] = cnt++;
            g[msi[u]].push_back(msi[v]);
        }
    }

    memset(dfsn, -1, sizeof(dfsn));
    for (int i = 1; i < cnt; ++i)
        if (dfsn[i] == -1) dfs(i);
    for (int i = 1; i < cnt; ++i)
        if (!visited[i]) dfs2(i);

    for (int i = 0; i < 10000; ++i) score[i] = 1;
    queue<int> q;
    for (int i = 1; i < cnt; ++i)
        if (ind[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g2[u]) {
            ind[v]--;
            score[v] += score[u];
            if (ind[v] == 0) q.push(v);
        }
    }
    string s;
    cin >> s;
    cout << score[msi[s]];

    return 0;
}