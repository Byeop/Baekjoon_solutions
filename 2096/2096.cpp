#include <bits/stdc++.h>

using namespace std;

char arr[3][100010];
int dp[3][100010];

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d %d %d", &arr[0][i], &arr[1][i], &arr[2][i]);

    for (int i = 0; i < 3; ++i) dp[i][0] = arr[i][0];
    for (int i = 1; i < n; ++i) {
        dp[0][i] = arr[0][i] + max(dp[0][i - 1], dp[1][i - 1]);
        dp[1][i] = arr[1][i] + max(dp[0][i - 1], max(dp[1][i - 1], dp[2][i - 1]));
        dp[2][i] = arr[2][i] + max(dp[1][i - 1], dp[2][i - 1]);
    }
    cout << max(dp[0][n - 1], max(dp[1][n - 1], dp[2][n - 1])) << " ";
    for (int i = 0; i < 3; ++i) dp[i][0] = arr[i][0];
    for (int i = 1; i < n; ++i) {
        dp[0][i] = arr[0][i] + min(dp[0][i - 1], dp[1][i - 1]);
        dp[1][i] = arr[1][i] + min(dp[0][i - 1], min(dp[1][i - 1], dp[2][i - 1]));
        dp[2][i] = arr[2][i] + min(dp[1][i - 1], dp[2][i - 1]);
    }
    cout << min(dp[0][n - 1], min(dp[1][n - 1], dp[2][n - 1]));

    return 0;
}