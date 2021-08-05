#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef struct _e {
    int x, y0, y1, i;
    bool operator<(_e &b) {
        if (x == b.x) return y0 < b.y0;
        return x < b.x;
    }
} event;

long long uf[50010], h[50010];
vector<event> xs, ys;

int find(int x) { return uf[x] < 0 ? x : uf[x] = find(uf[x]); }

void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (h[x] < h[y]) swap(x, y);
    uf[x] += uf[y];
    uf[y] = x;
    if (h[x] == h[y]) h[x]++;
}

void swipping(vector<event> &es) {
    for (int i = 1; i < es.size(); ++i)
        if (es[i - 1].x == es[i].x && es[i - 1].y1 >= es[i].y0) {
            merge(es[i - 1].i, es[i].i);
            es[i].y0 = es[i - 1].y0;
            es[i].y1 = max(es[i].y1, es[i - 1].y1);
        }
}

int main(void) {
    int n;
    scanf("%d", &n);
    int idx = 1;
    for (int i = 0; i < n; ++i) {
        int x0, y0, w, h;
        scanf("%d %d %d %d", &x0, &y0, &w, &h);
        int x1 = x0 + w, y1 = y0 + h;
        uf[i] = -h * w;
        xs.push_back({x0, y0, y1, i});
        xs.push_back({x1, y0, y1, i});
        ys.push_back({y0, x0, x1, i});
        ys.push_back({y1, x0, x1, i});
    }

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    swipping(xs);
    swipping(ys);

    long long ans = 0;
    for (int i = 0; i < n; ++i) ans = min(ans, uf[i]);
    printf("%lld", -ans);

    return 0;
}