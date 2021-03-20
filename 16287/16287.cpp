#include <bits/stdc++.h>

using namespace std;

int a[10000], dp[800000];

int main(void) {
    int n, w;
    scanf("%d%d", &w, &n);
    for (int i = 0; i < n; ++i) scanf("%d", a + i);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int s = a[i] + a[j];
            if (w - s <= 0)
                continue;
            else if (dp[w - s] && dp[w - s] < i) {
                printf("YES");
                return 0;
            }
            dp[s] = (dp[s] ? min(dp[s], j) : j);
        }
    }
    printf("NO");

    return 0;
}