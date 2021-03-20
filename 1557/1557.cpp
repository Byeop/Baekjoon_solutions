#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll mobius[1000100];
ll squareFree(ll n) {
    ll ret = 0;
    for (ll i = 1; i * i <= n; ++i) ret += mobius[i] * (n / (i * i));
    return ret;
}

int main(void) {
    mobius[1] = 1;
    for (int i = 1; i < 1000100; ++i)
        if (mobius[i] != 0)
            for (int j = 2 * i; j < 1000100; j += i) mobius[j] -= mobius[i];

    ll k;
    scanf("%lld", &k);

    ll l = 1, r = 1e12;
    while (l <= r) {
        ll m = (l + r) / 2;
        if (squareFree(m) < k)
            l = m + 1;
        else
            r = m - 1;
    }
    printf("%lld", l);

    return 0;
}