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

int main(void) {
    int n;
    cin >> n;
    vector<cpx> a(n * 2), b(n * 2, 0);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    for (int i = 0; i < n; ++i) cin >> b[n - i - 1];

    vector<cpx> c = multiply(a, b);
    int ans = 0;
    for (int i = n; i < 2 * n; ++i)
        ans = max(ans, (int)(c[i].real() + (c[i].real() > 0 ? 0.5 : -0.5)));
    cout << ans;

    return 0;
}