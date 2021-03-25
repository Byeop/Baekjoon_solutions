#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll fibo[55] = {
    1,
    1,
};

string findPath(int n, int u) {
    if (n == 1 || n == 0 || u == 1) return "";
    ll l = fibo[n - 2] + 1;
    if (l >= u)
        return "L" + findPath(n - 2, u - 1);
    else
        return "R" + findPath(n - 1, u - l);
}

int main(void) {
    ll n, s, e;
    cin >> n >> s >> e;

    for (int i = 2; i <= 50; ++i) fibo[i] = fibo[i - 1] + fibo[i - 2] + 1;
    string a = findPath(n, s);
    string b = findPath(n, e);
    while (a.size() && b.size() && a[0] == b[0]) {
        a.erase(a.begin());
        b.erase(b.begin());
    }
    cout << string(a.size(), 'U') + b;

    return 0;
}