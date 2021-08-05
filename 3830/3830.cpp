#include <bits/stdc++.h>

using namespace std;

typedef pair<int, long long> pii;

pii uf[100010];

pii find(int x) {
    if (uf[x].first == x) return uf[x];
    pii t = find(uf[x].first);
    t.second += uf[x].second;
    return uf[x] = t;
}

void merge(int x, int y, int d) {
    pii xp = find(x), yp = find(y);
    if (xp.first == yp.first) return;
    if (yp.second + d < xp.second)
        uf[yp.first] = pii(xp.first, xp.second - yp.second - d);
    else
        uf[xp.first] = pii(yp.first, yp.second + d - xp.second);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (1) {
        int n, m;
        cin >> n >> m;
        if (n == m && n == 0) break;
        for (int i = 1; i <= n; ++i) uf[i] = pii(i, 0);
        while (m--) {
            char q;
            int a, b, c;
            cin >> q >> a >> b;
            if (q == '!') {
                cin >> c;
                merge(a, b, c);  // a < b -- c
            } else {
                pii ap = find(a), bp = find(b);
                if (ap.first != bp.first)
                    printf("UNKNOWN\n");
                else
                    printf("%lld\n", ap.second - bp.second);
            }
        }
    }

    return 0;
}