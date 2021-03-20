#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(void) {
    ll n;
    scanf("%lld", &n);
    ll pi = n, prime = 2;
    while (prime * prime <= n) {
        if (n % prime == 0) pi = pi / prime * (prime - 1);
        while (n % prime == 0) n /= prime;
        prime++;
    }
    if (n != 1) pi = pi / n * (n - 1);
    printf("%lld", pi);

    return 0;
}