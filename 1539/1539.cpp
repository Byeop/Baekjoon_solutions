#include <bits/stdc++.h>

using namespace std;

map<int, int> bst;

int main(void) {
    int n;
    scanf("%d", &n);
    long long ans = 0;
    for (int i = 0, d; i < n; ++i) {
        scanf("%d", &d);
        int m = 0;
        auto it = bst.lower_bound(d);
        if (it != bst.end()) m = max(m, it->second);
        if (it != bst.begin()) m = max(m, (--it)->second);
        bst[d] = m + 1;
        ans += m + 1;
    }
    printf("%lld", ans);

    return 0;
}