#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii, ll> p;

ll w[262144];
vector<p> pos;
int n, c;

void inorder(int u) {
    if (n < u) return;
    inorder(u * 2);
    pos.push_back(p(pii(c++, log2(u)), w[u]));
    inorder(u * 2 + 1);
}

int main(void) {
    scanf("%d", &n);
    ll ans = -1e9;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", w + i);
        ans = max(ans, w[i]);
    }
    // edge case: all w is negative
    if (ans <= 0) {
        printf("%lld", ans);
        return 0;
    }

    int h = log2(n);
    inorder(1);
    sort(pos.begin(), pos.end());
    for (int a = 0; a <= h; ++a) {
        for (int b = a; b <= h; ++b) {
            ll sum = 0;
            for (p pp : pos) {
                int y = pp.first.second;
                ll d = pp.second;
                if (a <= y && y <= b) {
                    sum = max(sum + d, 0LL);
                    ans = max(ans, sum);
                }
            }
        }
    }
    printf("%lld", ans);

    return 0;
}