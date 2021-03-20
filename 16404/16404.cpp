#include <bits/stdc++.h>

using namespace std;

vector<int> g[100010];

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1, p; i <= n; ++i) {
        scanf("%d", &p);
        if (p != -1) g[p].push_back(i);
    }
    while (m--) {
        int cmd;
        scanf("%d", &cmd);
        if (cmd == 1) {
            int i, w;
            scanf("%d %d", &i, &w);
        }
    }

    return 0;
}