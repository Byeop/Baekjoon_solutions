#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

ll a[1000010], b[1000010];
priority_queue<ll> pq;

int main(void) {
    ll n, ans = 0;
    scanf("%lld", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", a + i);
        a[i] -= i;
        if (!pq.empty() && pq.top() > a[i]) {
            ans += pq.top() - a[i];
            pq.pop();
            pq.push(a[i]);
        }
        pq.push(a[i]);
        b[i] = pq.top();
    }
    for (int i = n - 2; i >= 0; --i) b[i] = min(b[i], b[i + 1]);
    for (int i = 0; i < n; ++i) printf("%lld\n", b[i] + i);

    return 0;
}