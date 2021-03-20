#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll R = 1000003;

typedef long long ll;
typedef vector<vector<ll>> matrix;
ll g[50][50];

matrix operator*(const matrix &a, matrix &b) {
    matrix c(a.size(), vector<ll>(a.size()));
    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < a.size(); ++j)
            for (int k = 0; k < a.size(); ++k) {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= R;
            }
    return c;
}

matrix pow(matrix a, ll n) {
    if (n == 1) return a;
    matrix ret = pow(a, n / 2);
    ret = ret * ret;
    if (n % 2) ret = ret * a;
    return ret;
}

int main(void) {
    ll n, s, e, T;
    scanf("%lld %lld %lld %lld", &n, &s, &e, &T);
    s--;
    e--;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) scanf("%1lld", &g[i][j]);

    matrix m(n * 5, vector<ll>(n * 5, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 1; j < 5; ++j) m[i * 5 + j][i * 5 + j - 1] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j] == 1)
                m[i * 5][j * 5] = 1;
            else if (g[i][j] > 1)
                m[i * 5][j * 5 + g[i][j] - 1] = 1;
        }
    }

    matrix ans = pow(m, T);
    printf("%lld", ans[s * 5][e * 5]);

    return 0;
}