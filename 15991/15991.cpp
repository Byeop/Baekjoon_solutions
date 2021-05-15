#include <bits/stdc++.h>

using namespace std;

long long dp[100010];
const int c = 1e9 + 9;

int main(void) {
    dp[0] = dp[1] = 1;
    dp[2] = dp[3] = 2;
    for (int i = 4; i <= 100000; ++i)
        for (int j = 0; j <= 3; ++j)
            if (i - j * 2 >= 0) dp[i] = (dp[i] + dp[i - j * 2]) % c;

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << dp[n] << "\n";
    }

    return 0;
}