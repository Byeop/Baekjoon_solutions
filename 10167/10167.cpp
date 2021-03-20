#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<pll, ll> gold;

struct node {
    ll sum, l, r, max;
};

node st[12010];
gold g[3000];
ll ypos[3000];

void update(ll p, ll v, ll n, ll l, ll r) {
    if (r < p || p < l) return;
    if (l == r) {
        st[n].sum += v;
        st[n].l += v;
        st[n].r += v;
        st[n].max += v;
    } else {
        ll m = (l + r) / 2;
        update(p, v, n * 2, l, m);
        update(p, v, n * 2 + 1, m + 1, r);
        st[n].sum = st[n * 2].sum + st[n * 2 + 1].sum;
        st[n].l = max(st[n * 2].l, st[n * 2].sum + st[n * 2 + 1].l);
        st[n].r = max(st[n * 2 + 1].r, st[n * 2 + 1].sum + st[n * 2].r);
        st[n].max = max(
            max(max(st[n * 2].r + st[n * 2 + 1].l, st[n * 2].max), max(st[n * 2 + 1].max, st[n].l)),
            st[n].r);
    }
}

ll query(ll l, ll r, ll n, ll nl, ll nr) {
    if (nr < l || r < nl)
        return 0;
    else if (l <= nl && nr <= r)
        return st[n].max;
    ll m = (nl + nr) / 2;
    return max(query(l, r, n * 2, nl, m), query(l, r, n * 2 + 1, m + 1, nr));
}

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        ll x, y, w;
        scanf("%lld%lld%lld", &x, &y, &w);
        g[i] = gold(pll(x, y), w);
        ypos[i] = y;
    }

    sort(ypos, ypos + n);
    sort(g, g + n);
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        memset(st, 0, sizeof(st));
        if (i && g[i - 1].first.first == g[i].first.first) continue;
        for (int j = i; j < n; ++j) {
            ll p = lower_bound(ypos, ypos + n, g[j].first.second) - ypos;
            update(p, g[j].second, 1, 0, n - 1);
            if (j == n - 1 || g[j].first.first != g[j + 1].first.first)
                ans = max(ans, query(0, n - 1, 1, 0, n - 1));
        }
    }
    printf("%lld", ans);

    return 0;
}