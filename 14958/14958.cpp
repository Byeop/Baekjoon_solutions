#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1);
typedef complex<double> cpx;

void FFT(vector<cpx> &f, cpx w) {
    int n = f.size();
    if (n == 1) return;

    vector<cpx> even(n / 2), odd(n / 2);
    for (int i = 0; i < n; ++i) (i % 2 ? odd : even)[i / 2] = f[i];

    FFT(even, w * w);
    FFT(odd, w * w);

    cpx wp(1, 0);
    for (int i = 0; i < n / 2; ++i) {
        f[i] = even[i] + wp * odd[i];
        f[i + n / 2] = even[i] - wp * odd[i];
        wp *= w;
    }
}

vector<cpx> multiply(vector<cpx> a, vector<cpx> b) {
    int n = 1;
    while (n < a.size() + 1 || n < b.size() + 1) n *= 2;
    n *= 2;
    a.resize(n);
    b.resize(n);
    vector<cpx> c(n);

    cpx w(cos(2 * PI / n), sin(2 * PI / n));

    FFT(a, w);
    FFT(b, w);

    for (int i = 0; i < n; ++i) c[i] = a[i] * b[i];

    FFT(c, cpx(1, 0) / w);
    for (int i = 0; i < n; ++i) {
        c[i] /= cpx(n, 0);
        c[i] = cpx(round(c[i].real()), round(c[i].imag()));
    }
    return c;
}

int co[120], res[200020];

int main(void) {
    int n, m;
    string in, choices;
    cin >> n >> m >> in >> choices;
    co['R'] = 0;
    co['P'] = 1;
    co['S'] = 2;

    vector<cpx> a(n), b(m);
    for (int i = 0; i < n; ++i) a[i] = (co[in[i]] + 1) % 3;
    for (int i = 0; i < m; ++i) b[i] = co[choices[i]];
    for (int i = 0; i < 3; ++i) {
        vector<cpx> u(n + m), v(m);
        for (int j = 0; j < n; ++j) u[j] = a[j].real() == i;
        for (int j = 0; j < m; ++j) v[j] = b[m - j - 1].real() == i;
        vector<cpx> ret = multiply(u, v);
        for (int j = 0; j < n + m; ++j) res[j] += ret[j].real();
    }
    cout << *max_element(res + m - 1, res + n + m);

    return 0;
}