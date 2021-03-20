#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll cnt[10];

void calc(int n, int pow) {
    while (n > 0) {
        cnt[n % 10] += pow;
        n /= 10;
    }
}

void solve(int a, int b, int pow) {
    while (a % 10 != 0 && a <= b) {
        calc(a, pow);
        ++a;
    }
    if (a > b) return;
    while (b % 10 != 9 && a <= b) {
        calc(b, pow);
        --b;
    }
    ll c = b / 10 - a / 10 + 1;
    for (int i = 0; i < 10; ++i) cnt[i] += c * pow;
    solve(a / 10, b / 10, pow * 10);
}

int main(void) {
    ll n;
    scanf("%lld", &n);
    solve(1, n, 1);
    for (int i = 0; i < 10; ++i) printf("%lld ", cnt[i]);

    return 0;
}