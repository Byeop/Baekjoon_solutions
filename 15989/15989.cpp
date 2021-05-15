#include <bits/stdc++.h>

using namespace std;

int dp[10010][4];

int main(void) {
    dp[1][1] = dp[2][1] = dp[2][2] = dp[3][1] = dp[3][2] = dp[3][3] = 1;
    for (int i = 4; i <= 10000; ++i) {
        dp[i][1] = 1;
        dp[i][2] = dp[i - 2][1] + dp[i - 2][2];
        dp[i][3] = dp[i - 3][1] + dp[i - 3][2] + dp[i - 3][3];
    }

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << dp[n][1] + dp[n][2] + dp[n][3] << "\n";
    }

    return 0;
}