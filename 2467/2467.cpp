#include <bits/stdc++.h>

using namespace std;

int p[100010];

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> p[i];

    int i = 0, j = n - 1, sum = abs(p[i] + p[j]);
    int a = p[i], b = p[j];
    while (i < j) {
        if (abs(p[i] + p[j]) < sum) {
            sum = abs(p[i] + p[j]);
            a = p[i], b = p[j];
        }
        if (p[i] + p[j] < 0)
            ++i;
        else
            --j;
    }
    cout << a << " " << b;

    return 0;
}