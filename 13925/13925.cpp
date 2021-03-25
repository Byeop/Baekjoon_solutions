#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 1 << 20, mod = 1e9 + 7;
ll st[MAX * 2], a[MAX * 2], b[MAX * 2];

void construct() {
    for (int i = MAX - 1; i > 0; --i) st[i] = (st[i * 2] + st[i * 2 + 1]) % mod;
}

void propagate(int n, int nl, int nr) {
    if (a[n] == 1 && b[n] == 0) return;
    if (n < MAX) {
        for (int i : {n * 2, n * 2 + 1}) {
            a[i] = (a[n] * a[i]) % mod;
            b[i] = (a[n] * b[i] + b[n]) % mod;
        }
    }
    st[n] = (a[n] * st[n] + (nr - nl + 1) * b[n]) % mod;
    a[n] = 1, b[n] = 0;
}

void update(int l, int r, int n, int nl, int nr, ll m, ll s) {
    propagate(n, nl, nr);
    if (nr < l || r < nl) return;
    if (l <= nl && nr <= r) {
        a[n] = (a[n] * m) % mod;
        b[n] = (b[n] * m) % mod;
        b[n] = (b[n] + s) % mod;
        propagate(n, nl, nr);
        return;
    }
    int mid = nl + nr >> 1;
    update(l, r, n * 2, nl, mid, m, s);
    update(l, r, n * 2 + 1, mid + 1, nr, m, s);
    st[n] = (st[n * 2] + st[n * 2 + 1]) % mod;
}

ll sum(int l, int r, int n, int nl, int nr) {
    propagate(n, nl, nr);
    if (nr < l || r < nl) return 0;
    if (l <= nl && nr <= r) return st[n] % mod;
    int mid = nl + nr >> 1;
    return (sum(l, r, n * 2, nl, mid) + sum(l, r, n * 2 + 1, mid + 1, nr)) % mod;
}

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> st[i + MAX];

    for (int i = 0; i < MAX * 2; ++i) a[i] = 1;
    construct();

    int q;
    cin >> q;
    while (q--) {
        ll c, a, b, v;
        cin >> c >> a >> b;
        if (c != 4) cin >> v;
        if (c == 1)
            update(a, b, 1, 1, MAX, 1, v);
        else if (c == 2)
            update(a, b, 1, 1, MAX, v, 0);
        else if (c == 3)
            update(a, b, 1, 1, MAX, 0, v);
        else
            cout << sum(a, b, 1, 1, MAX) << "\n";
    }

    return 0;
}