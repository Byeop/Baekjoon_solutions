#include <bits/stdc++.h>

using namespace std;

#define left(n) (n * 2)
#define right(n) ((n * 2) + 1)

typedef long long ll;

const ll MAX = 2097152;
ll st[MAX * 2];
ll n, m, k;

void init() {
    for (int i = MAX - 1; i > 0; --i) st[i] = st[left(i)] + st[right(i)];
}

ll sum(ll l, ll r, int node, int nodeL, int nodeR) {
    if (r < nodeL || l > nodeR) return 0;
    if (l <= nodeL && nodeR <= r) return st[node];
    int m = nodeL + nodeR >> 1;
    return sum(l, r, left(node), nodeL, m) +
           sum(l, r, right(node), m + 1, nodeR);
}

ll sum(ll l, ll r) { return sum(l, r, 1, 0, MAX - 1); }

void update(int i, ll v) {
    i += MAX;
    st[i] = v;
    while (i > 1) {
        i /= 2;
        st[i] = st[left(i)] + st[right(i)];
    }
}

int main(void) {
    scanf("%lld %lld %lld", &n, &m, &k);
    for (int i = 0; i < n; ++i) scanf("%lld", st + i + MAX);
    init();
    for (int T = 0; T < m + k; ++T) {
        ll a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);
        if (a == 1)
            update(b - 1, c);
        else
            printf("%lld\n", sum(b - 1, c - 1, 1, 0, MAX - 1));
    }

    return 0;
}