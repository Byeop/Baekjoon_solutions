#include <bits/stdc++.h>

using namespace std;

long long dp[1000100];
const long long c = 1000000009;

int main(void) {
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;
    for (int i = 4; i < 1000100; ++i) dp[i] = (dp[i - 1] + dp[i - 2] + dp[i - 3]) % c;

    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        printf("%lld\n", dp[n]);
    }

    return 0;
}