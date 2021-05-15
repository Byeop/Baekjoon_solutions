#include <bits/stdc++.h>

using namespace std;

int a[100010];

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, s;
    cin >> n >> s;
    for (int i = 0; i < n; ++i) cin >> a[i];

    int i = 0, j = 0, sum = a[0];
    int ans = 100010;
    while (i <= j) {
        if (sum >= s) {
            ans = min(ans, j - i + 1);
            sum -= a[i++];
        } else if (j < n - 1)
            sum += a[++j];
        else
            break;
    }
    cout << (ans > n ? 0 : ans);

    return 0;
}