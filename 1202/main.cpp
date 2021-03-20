#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

ll m[300010], v[300010], c[300010];
priority_queue<pll> q1, q2;

int main(void) {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%lld %lld", m + i, v + i);
        q1.push(pll(-m[i], v[i]));
    }
    for (int i = 0; i < k; ++i) scanf("%lld", c + i);
    sort(c, c + k);

    ll ans = 0;
    for (int i = 0; i < k; ++i) {
        while (!q1.empty() && -q1.top().first <= c[i]) {
            auto t = q1.top();
            q1.pop();
            ll v = t.second, m = -t.first;
            q2.push(pll(v, -m));
        }
        if (!q2.empty()) {
            ans += q2.top().first;
            q2.pop();
        }
    }
    printf("%lld", ans);

    return 0;
}