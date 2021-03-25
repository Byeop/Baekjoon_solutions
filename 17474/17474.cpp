// #include <bits/stdc++.h>

// #define left(n) (n << 1)
// #define right(n) ((n << 1) + 1)

// using namespace std;

// typedef long long ll;

// struct node {
//     ll mx, mx2, cnt, sum;
// };

// const int MAX = 1048576;
// node st[MAX * 2];
// ll arr[MAX];

// node mergeTree(node a, node b) {
//     if (a.mx == b.mx) return {a.mx, max(a.mx2, b.mx), a.cnt + b.cnt, a.sum + b.sum};
//     if (a.mx > b.mx) swap(a, b);
//     return {b.mx, max(a.mx, b.mx2), b.cnt, a.sum + b.sum};
// }

// void construct() {
//     for (int i = MAX; i < MAX * 2; ++i) st[i] = {arr[i - MAX], -1, 1, arr[i - MAX]};
//     for (int i = MAX - 1; i > 0; --i) st[i] = mergeTree(st[left(i)], st[right(i)]);
// }

// void propagate(int n, int nl, int nr) {
//     if (n >= MAX) return;
//     for (auto i : {left(n), right(n)}) {
//         if (st[n].mx < st[i].mx) {
//             st[i].sum -= st[i].cnt * (st[i].mx - st[n].mx);
//             st[i].mx = st[n].mx;
//         }
//     }
// }

// void update(int l, int r, ll v, int n, int nl, int nr) {
//     propagate(n, nl, nr);
//     if (nr < l || r < nl || st[n].mx <= v) return;
//     if (l <= nl && nr <= r && st[n].mx2 < v) {
//         st[n].sum -= st[n].cnt * (st[n].mx - v);
//         st[n].mx = v;
//         propagate(n, nl, nr);
//         return;
//     }
//     int mid = nl + nr >> 1;
//     update(l, r, v, left(n), nl, mid);
//     update(l, r, v, right(n), mid + 1, nr);
//     st[n] = mergeTree(st[left(n)], st[right(n)]);
// }

// ll max(int l, int r, int n, int nl, int nr) {
//     propagate(n, nl, nr);
//     if (nr < l || r < nl) return -1;
//     if (l <= nl && nr <= r) return st[n].mx;
//     int mid = nl + nr >> 1;
//     return max(max(l, r, left(n), nl, mid), max(l, r, right(n), mid + 1, nr));
// }

// ll sum(int l, int r, int n, int nl, int nr) {
//     propagate(n, nl, nr);
//     if (nr < l || r < nl) return 0;
//     if (l <= nl && nr <= r) return st[n].sum;
//     int mid = nl + nr >> 1;
//     return sum(l, r, left(n), nl, mid) + sum(l, r, right(n), mid + 1, nr);
// }

// int main(void) {
//     ios::sync_with_stdio(0);
//     cin.tie(0);

//     for (int i = 0; i < MAX; ++i) arr[i] = 1e10;
//     int n;
//     cin >> n;
//     for (int i = 0; i < n; ++i) cin >> arr[i];

//     int m;
//     cin >> m;
//     construct();
//     while (m--) {
//         ll c, a, b, x;
//         cin >> c >> a >> b;
//         if (c == 1) {
//             cin >> x;
//             update(a, b, x, 1, 1, MAX);
//         } else if (c == 2)
//             cout << max(a, b, 1, 1, MAX) << '\n';
//         else
//             cout << sum(a, b, 1, 1, MAX) << '\n';
//     }

//     return 0;
// }

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct node {
    ll mx, mx2, cnt, sum;
};

ll arr[1010101];
node tree[4040404];

node merge(node a, node b) {
    if (a.mx == b.mx) return {a.mx, max(a.mx2, b.mx2), a.cnt + b.cnt, a.sum + b.sum};
    if (a.mx > b.mx) swap(a, b);
    return {b.mx, max(a.mx, b.mx2), b.cnt, a.sum + b.sum};
}

node init(int n, int s, int e) {
    if (s == e) return tree[n] = {arr[s], -1, 1, arr[s]};
    int m = s + e >> 1;
    return tree[n] = merge(init(n * 2, s, m), init(n * 2 + 1, m + 1, e));
}

void push(int n, int s, int e) {
    if (s == e) return;
    for (auto i : {n * 2, n * 2 + 1}) {
        if (tree[n].mx < tree[i].mx) {
            tree[i].sum -= tree[i].cnt * (tree[i].mx - tree[n].mx);
            tree[i].mx = tree[n].mx;
        }
    }
}

void update(int n, int s, int e, int l, int r, ll v) {
    push(n, s, e);
    if (r < s || e < l || tree[n].mx <= v) return;
    if (l <= s && e <= r && tree[n].mx2 < v) {
        tree[n].sum -= tree[n].cnt * (tree[n].mx - v);
        tree[n].mx = v;
        push(n, s, e);
        return;
    }
    int m = s + e >> 1;
    update(n * 2, s, m, l, r, v);
    update(n * 2 + 1, m + 1, e, l, r, v);
    tree[n] = merge(tree[n * 2], tree[n * 2 + 1]);
}

ll getmax(int n, int s, int e, int l, int r) {
    push(n, s, e);
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return tree[n].mx;
    int m = s + e >> 1;
    return max(getmax(n * 2, s, m, l, r), getmax(n * 2 + 1, m + 1, e, l, r));
}

ll getsum(int n, int s, int e, int l, int r) {
    push(n, s, e);
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return tree[n].sum;
    int m = s + e >> 1;
    return getsum(n * 2, s, m, l, r) + getsum(n * 2 + 1, m + 1, e, l, r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> arr[i];

    init(1, 1, n);
    int q;
    cin >> q;
    while (q--) {
        ll op, a, b, x;
        cin >> op >> a >> b;
        if (op == 1) {
            cin >> x;
            update(1, 1, n, a, b, x);
        } else if (op == 2)
            cout << getmax(1, 1, n, a, b) << "\n";
        else
            cout << getsum(1, 1, n, a, b) << "\n";
    }
}