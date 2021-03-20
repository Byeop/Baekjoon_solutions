#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, pii> event;

const int MAX = 16284;
vector<event> events;
int st[MAX * 2], lazy[MAX * 2];

void update(int v, int l, int r, int n, int nl, int nr) {
    if (nr < l || r < nl) return;
    if (l <= nl && nr <= r)
        lazy[n] += v;
    else {
        int m = (nl + nr) / 2;
        update(v, l, r, n * 2, nl, m);
        update(v, l, r, n * 2 + 1, m + 1, nr);
    }
    if (lazy[n] > 0)
        st[n] = nr - nl + 1;
    else {
        if (nl != nr)
            st[n] = st[n * 2] + st[n * 2 + 1];
        else
            st[n] = 0;
    }
}

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        double a, b, c, d;
        scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
        int x0, y0, x1, y1;
        x0 = a * 10;
        y0 = b * 10;
        x1 = x0 + c * 10;
        y1 = y0 + d * 10;
        events.push_back(event(pii(x0, 1), pii(y0, y1)));
        events.push_back(event(pii(x1, -1), pii(y0, y1)));
    }

    sort(events.begin(), events.end());
    int area = 0;
    update(1, events[0].second.first, events[0].second.second - 1, 1, 0, MAX - 1);
    for (int i = 1; i < events.size(); ++i) {
        int dx = events[i].first.first - events[i - 1].first.first;
        int s = events[i].second.first, e = events[i].second.second - 1;
        area += st[1] * dx;
        update(events[i].first.second, s, e, 1, 0, MAX - 1);
    }
    if (area / 100 * 100 == area)
        printf("%d", area / 100);
    else
        printf("%.2lf", area / 100.0);

    return 0;
}