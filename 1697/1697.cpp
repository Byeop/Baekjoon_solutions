#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
queue<pii> q;

int main(void) {
    int n, k;
    scanf("%d%d", &n, &k);
    q.push(pii(n, 0));
    while (!q.empty()) {
        auto f = q.front();
        q.pop();
        int curPosition = f.first, curTime = f.second;
    }
    return 0;
}