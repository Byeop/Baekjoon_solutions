#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<vector<ll>> matrix;

matrix operator*(const matrix &a, const matrix &b) {
    ll s = a.size();
    matrix ret(s, vector<ll>(s, 0));
    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < s; ++j) {
            for (int k = 0; k < s; ++k) ret[i][j] += a[i][k] * b[k][j];
            ret[i][j] %= 1000;
        }
    }
    return ret;
}

matrix operator*=(const matrix &a, const matrix &b) { return a * b; }

matrix pow(matrix a, int n) {
    ll s = a.size();
    matrix ret(s, vector<ll>(s, 0));
    for (int i = 0; i < s; ++i) ret[i][i] = 1;
    while (n > 0) {
        if (n % 2) ret = ret * a;
        n /= 2;
        a = a * a;
    }
    return ret;
}

int main(void) {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        ll n;
        scanf("%lld", &n);
        matrix a = {{6, -4}, {1, 0}};
        matrix ret = pow(a, n - 1);
        ll ans = ((ret[1][0] * 28 + ret[1][1] * 6 - 1) % 1000 + 1000) % 1000;
        printf("Case #%d: %03lld\n", t, ans);
    }

    return 0;
}