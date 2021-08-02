#include <bits/stdc++.h>

using namespace std;

typedef vector<int> bin;

bin getBin(int x) {
    vector<int> ret;
    while (x > 0) {
        ret.push_back(x & 1);
        x >>= 1;
    }
    while (ret.size() < 5) ret.push_back(0);
    reverse(ret.begin(), ret.end());
    return ret;
}

int neg(int x) {
    if (x < 250000)
        return x + 250000;
    else
        return x - 250000;
}

int ai[50010];
vector<int> g[500010];

int main(void) {
    int n, m;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", ai + i);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        char o;
        int a, b, c;
        scanf(" %c %d %d %d", &o, &a, &b, &c);

        if (a < b) swap(a, b);
        bin c_bin = getBin(c);
        for (int i = 0; i < 5; ++i) {
            if (o == '&' && c_bin[i] == 0) {
                g[a * 5 + i].push_back(neg(b * 5 + i));
                g[b * 5 + i].push_back(neg(a * 5 + i));
            } else if (o == '|' && c_bin[i] == 1) {
                g[neg(a * 5 + i)].push_back(b * 5 + i);
                g[neg(b * 5 + i)].push_back(a * 5 + i);
            }
        }
    }

    return 0;
}