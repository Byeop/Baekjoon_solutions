#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 1 << 20;
ll st[MAX * 2], lazy[MAX * 2];

void construct() {
    for (int i = MAX - 1; i > 0; --i) st[i] = st[i * 2] + st[i * 2 + 1];
}

void propagate(int n, int nl, int nr) {
    if (lazy[n] != 0) {
        if (n < MAX) {
            lazy[n * 2] += lazy[n];
            lazy[n * 2 + 1] += lazy[n];
        }
        st[n] += lazy[n] * (nr - nl + 1);
        lazy[n] = 0;
    }
}

void update(int l, int r, int n, int nl, int nr, ll k) {
    propagate(n, nl, nr);
    if (nr < l || r < nl) return;
    if (l <= nl && nr <= r) {
        lazy[n] += k;
        propagate(n, nl, nr);
        return;
    }
    int mid = (nl + nr) / 2;
    update(l, r, n * 2, nl, mid, k);
    update(l, r, n * 2 + 1, mid + 1, nr, k);
    st[n] = st[n * 2] + st[n * 2 + 1];
}

ll sum(int l, int r, int n, int nl, int nr) {
    propagate(n, nl, nr);
    if (nr < l || r < nl) return 0;
    if (l <= nl && nr <= r) return st[n];
    int mid = (nl + nr) / 2;
    return sum(l, r, n * 2, nl, mid) + sum(l, r, n * 2 + 1, mid + 1, nr);
}

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> st[MAX + i];

    construct();
    int m;
    cin >> m;
    while (m--) {
        int c, i, j, k;
        cin >> c;
        if (c == 1) {
            cin >> i >> j >> k;
            update(i, j, 1, 1, MAX, k);
        } else {
            cin >> i;
            cout << sum(i, i, 1, 1, MAX) << '\n';
        }
    }

    return 0;
}