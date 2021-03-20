#include <bits/stdc++.h>

using namespace std;

int p[510], dp[510][510];

int solve(int i, int j) {
    if (i == j) return 0;
    int &ret = dp[i][j];
    if (ret != -1) return ret;
    ret = 1e9;
    for (int k = i; k < j; ++k)
        ret = min(ret, solve(i, k) + solve(k + 1, j) + p[i - 1] * p[k] * p[j]);
    return ret;
}

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d %d", p + i, p + i + 1);

    memset((void *)dp, -1, sizeof(dp));
    printf("%d", solve(1, n));

    return 0;
}