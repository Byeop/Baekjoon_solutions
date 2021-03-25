#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct node {
    ll m1, m2, sum;
};

node st[400010];
ll lazy[400010], lazy2[400010];

node merge(node a, node b) { return {max(a.m1, b.m1), min(a.m2, b.m2), a.sum + b.sum}; }

void propagate(int n, int nl, int nr) {
    if (lazy[n] == 0 && lazy2[n] == 0) return;
    if (!lazy2[n]) {
        st[n].m1 += lazy[n];
        st[n].m2 += lazy[n];
        st[n].sum += (nr - nl + 1) * lazy[n];
        if (nl != nr) {
            lazy[n * 2] += lazy[n];
            lazy[n * 2 + 1] += lazy[n];
        }
    } else {
        st[n].m1 = st[n].m2 = lazy[n] + lazy2[n];
        st[n].sum = (nr - nl + 1) * (lazy[n] + lazy2[n]);
        if (nl != nr) {
            lazy[n * 2] = lazy[n * 2 + 1] = lazy[n];
            lazy2[n * 2] = lazy2[n * 2 + 1] = lazy2[n];
        }
    }
    lazy[n] = lazy2[n] = 0;
}

void add(int l, int r, int n, int nl, int nr, ll v) {
    propagate(n, nl, nr);
    if (nr < l || r < nl) return;
    if (l <= nl && nr <= r) {
        lazy[n] = v;
        propagate(n, nl, nr);
        return;
    }
    int mid = nl + nr >> 1;
    add(l, r, n * 2, nl, mid, v);
    add(l, r, n * 2 + 1, mid + 1, nr, v);
    st[n] = merge(st[n * 2], st[n * 2 + 1]);
}

void square(int l, int r, int n, int nl, int nr) {
    propagate(n, nl, nr);
    if (nr < l || r < nl) return;
    if (l <= nl && nr <= r) {
        if (floor(sqrt(st[n].m1)) == floor(sqrt(st[n].m2))) {
            lazy2[n] = floor(sqrt(st[n].m1));
            propagate(n, nl, nr);
            return;
        }
        if (st[n].m2 + 1 == st[n].m1) {
            lazy[n] = floor(sqrt(st[n].m1)) - st[n].m1;
            propagate(n, nl, nr);
            return;
        }
    }
    int mid = nl + nr >> 1;
    square(l, r, n * 2, nl, mid);
    square(l, r, n * 2 + 1, mid + 1, nr);
    st[n] = merge(st[n * 2], st[n * 2 + 1]);
}

ll sum(int l, int r, int n, int nl, int nr) {
    propagate(n, nl, nr);
    if (nr < l || r < nl) return 0;
    if (l <= nl && nr <= r) return st[n].sum;
    int mid = nl + nr >> 1;
    return sum(l, r, n * 2, nl, mid) + sum(l, r, n * 2 + 1, mid + 1, nr);
}

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        ll t;
        cin >> t;
        add(i, i, 1, 1, n, t);
    }

    int q;
    cin >> q;
    while (q--) {
        ll cmd, a, b, x;
        cin >> cmd >> a >> b;
        if (cmd == 1) {
            cin >> x;
            add(a, b, 1, 1, n, x);
        } else if (cmd == 2)
            square(a, b, 1, 1, n);
        else
            cout << sum(a, b, 1, 1, n) << '\n';
    }

    return 0;
}