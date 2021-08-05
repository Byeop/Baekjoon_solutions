#include <bits/stdc++.h>

using namespace std;

int p[200010], q[400010][3], uf[200010], h[200010];

int find(int x) { return uf[x] == x ? x : uf[x] = find(uf[x]); }
void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (h[x] < h[y]) swap(x, y);
    uf[y] = x;
    if (h[x] == h[y]) h[x]++;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 2; i <= n; ++i) scanf("%d", p + i);
    m += n - 1;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &q[i][0], &q[i][1]);
        if (q[i][0] == 1) scanf("%d", &q[i][2]);
    }
    for (int i = 1; i <= n; ++i) uf[i] = i, h[i] = 0;
    vector<int> st;
    for (int i = m - 1; i >= 0; --i) {
        if (q[i][0] == 0)
            merge(q[i][1], p[q[i][1]]);
        else
            st.push_back(find(q[i][1]) == find(q[i][2]));
    }
    for (int i = st.size() - 1; i >= 0; --i) printf("%s\n", st[i] ? "YES" : "NO");

    return 0;
}