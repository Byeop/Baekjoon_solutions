#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct node {
    ll mn, mx, sum;
};

node tree[400010];
ll tmp1[400010], tmp2[400010];

node merge(node a, node b) { return {min(a.mn, b.mn), max(a.mx, b.mx), a.sum + b.sum}; }

void push(int n, int s, int e) {
    if (tmp2[n] <= -1e18) {
        tree[n].mx += tmp1[n];
        tree[n].mn += tmp1[n];
        tree[n].sum += (e - s + 1) * tmp1[n];
        if (s ^ e) {
            tmp1[n * 2] += tmp1[n];
            tmp1[n * 2 + 1] += tmp1[n];
        }
    } else {
        tree[n].mx = tree[n].mn = tmp1[n] + tmp2[n];
        tree[n].sum = (e - s + 1) * (tmp1[n] + tmp2[n]);
        if (s ^ e) {
            tmp1[n * 2] = tmp1[n];
            tmp1[n * 2 + 1] = tmp1[n];
            tmp2[n * 2] = tmp2[n];
            tmp2[n * 2 + 1] = tmp2[n];
        }
    }
    tmp1[n] = 0, tmp2[n] = -1e18;
}

void add(int n, int s, int e, int l, int r, ll v) {
    push(n, s, e);
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
        tmp1[n] = v;
        push(n, s, e);
        return;
    }
    int m = s + e >> 1;
    add(n * 2, s, m, l, r, v);
    add(n * 2 + 1, m + 1, e, l, r, v);
    tree[n] = merge(tree[n * 2], tree[n * 2 + 1]);
}

void div(int n, int s, int e, int l, int r, ll d) {
    push(n, s, e);
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
        if (floor((double)tree[n].mn / d) == floor((double)tree[n].mx / d)) {
            tmp2[n] = floor((double)tree[n].mn / d);
            push(n, s, e);
            return;
        }
        if (tree[n].mn + 1 == tree[n].mx) {
            tmp1[n] = floor((double)tree[n].mn / d) - tree[n].mn;
            push(n, s, e);
            return;
        }
    }
    int m = s + e >> 1;
    div(n * 2, s, m, l, r, d);
    div(n * 2 + 1, m + 1, e, l, r, d);
    tree[n] = merge(tree[n * 2], tree[n * 2 + 1]);
}

node query(int n, int s, int e, int l, int r) {
    push(n, s, e);
    if (r < s || e < l) return {(ll)1e18, (ll)-1e18, 0};
    if (l <= s && e <= r) return tree[n];
    int m = s + e >> 1;
    return merge(query(n * 2, s, m, l, r), query(n * 2 + 1, m + 1, e, l, r));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 400010; i++) tmp2[i] = -1e18;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        add(1, 0, n - 1, i, i, t);
    }

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            ll a, b, c;
            cin >> a >> b >> c;
            add(1, 0, n - 1, a, b, c);
        } else if (op == 2) {
            ll a, b, c;
            cin >> a >> b >> c;
            div(1, 0, n - 1, a, b, c);
        } else {
            int a, b;
            cin >> a >> b;
            node now = query(1, 0, n - 1, a, b);
            if (op == 3)
                cout << now.mn << "\n";
            else
                cout << now.sum << "\n";
        }
    }

    return 0;
}