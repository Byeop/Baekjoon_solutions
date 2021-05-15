#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll dp[1000100], parent[1000100];

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    dp[1] = 0;
    dp[2] = dp[3] = 1;
    parent[2] = parent[3] = 1;
    for (int i = 4; i <= n; ++i) {
        dp[i] = dp[i - 1] + 1;
        parent[i] = i - 1;
        if (i % 3 == 0 && dp[i] > dp[i / 3] + 1) {
            dp[i] = dp[i / 3] + 1;
            parent[i] = i / 3;
        }
        if (i % 2 == 0 && dp[i] > dp[i / 2] + 1) {
            dp[i] = dp[i / 2] + 1;
            parent[i] = i / 2;
        }
    }
    cout << dp[n] << "\n";
    for (int i = n; i != 0; i = parent[i]) cout << i << " ";

    return 0;
}