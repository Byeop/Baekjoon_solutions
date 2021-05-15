#include <bits/stdc++.h>

using namespace std;

long long dp[1010][1010];
const int c = 1e9 + 9;

int main(void) {
    dp[1][1] = dp[2][1] = dp[2][2] = dp[3][1] = 1;
    dp[3][2] = 2;
    dp[3][3] = 1;
    for (int i = 4; i <= 1000; ++i)
        for (int j = 2; j <= 1000; ++j)
            for (int k = 1; k <= 3; ++k) {
                dp[i][j] += dp[i - k][j - 1];
                dp[i][j] %= c;
            }

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        auto ans = 0;
        for (int i = 1; i <= m; ++i) ans = (ans + dp[n][i]) % c;
        cout << ans << "\n";
    }

    return 0;
}