#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

vector<int> st1, st2;

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int t;
        scanf("%d", &t);
        st1.push_back(t);
    }

    int last = n, a = 1, b = 2;
    vector<pii> ans;
    while (last >= 1) {
        while (!st1.empty() && st1.back() != last) {
            st2.push_back(st1.back());
            st1.pop_back();
            ans.push_back({a, b});
        }
        if (!st1.empty() && st1.back() == last) {
            st1.pop_back();
            ans.push_back({a, 3});
            last--;
        }
        if (st1.empty()) {
            swap(st1, st2);
            swap(a, b);
        }
    }

    printf("%d\n", ans.size());
    for (auto p : ans) printf("%d %d\n", p.first, p.second);

    return 0;
}