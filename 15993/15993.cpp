#include <bits/stdc++.h>

using namespace std;

long long dp[100010][2];
const int c = 1e9 + 9;

int main(void) {
    dp[1][0] = 1;
    dp[2][0] = dp[2][1] = 1;
    dp[3][0] = dp[3][1] = 2;
    for (int i = 4; i <= 100000; ++i) {
        for (int j = 1; j <= 3; ++j) {
            dp[i][0] += dp[i - j][1];
            dp[i][1] += dp[i - j][0];
            dp[i][0] %= c;
            dp[i][1] %= c;
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << dp[n][0] << " " << dp[n][1] << "\n";
    }

    return 0;
}