#include <bits/stdc++.h>

using namespace std;

vector<int> v;

int n, k, c;

void dfs(int s) {
    if (s > n) return;
    if (s == n) {
        c++;
        if (c == k) {
            for (int i = 0; i < v.size() - 1; ++i) printf("%d+", v[i]);
            printf("%d", v.back());
            exit(0);
        }
    }
    for (int i = 1; i <= 3; ++i) {
        v.push_back(i);
        dfs(s + i);
        v.pop_back();
    }
}

int main(void) {
    cin >> n >> k;
    dfs(0);
    printf("-1");
    return 0;
}