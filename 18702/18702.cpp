#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse")
#include <bits/stdc++.h>

inline int readChar();
template <class T = int>
inline T readInt();
template <class T>
inline void writeInt(T x, char end = 0);
inline void writeChar(int x);
inline void writeWord(const char *s);
static const int buf_size = 1 << 18;
inline int getChar() {
    static char buf[buf_size];
    static int len = 0, pos = 0;
    if (pos == len) pos = 0, len = fread(buf, 1, buf_size, stdin);
    if (pos == len) return -1;
    return buf[pos++];
}
inline int readChar() {
    int c = getChar();
    while (c <= 32) c = getChar();
    return c;
}
template <class T>
inline T readInt() {
    int s = 1, c = readChar();
    T x = 0;
    if (c == '-') s = -1, c = getChar();
    while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = getChar();
    return s == 1 ? x : -x;
}
static int write_pos = 0;
static char write_buf[buf_size];
inline void writeChar(int x) {
    if (write_pos == buf_size) fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
    write_buf[write_pos++] = x;
}
template <class T>
inline void writeInt(T x, char end) {
    if (x < 0) writeChar('-'), x = -x;
    char s[24];
    int n = 0;
    while (x || !n) s[n++] = '0' + x % 10, x /= 10;
    while (n--) writeChar(s[n]);
    if (end) writeChar(end);
}
inline void writeWord(const char *s) {
    while (*s) writeChar(*s++);
}
struct Flusher {
    ~Flusher() {
        if (write_pos) fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
    }
} flusher;

using namespace std;

typedef long long ll;

struct node {
    ll m1, m2, sum;
};

node st[1 << 18];
ll lazy[1 << 18], lazy2[1 << 18];

node merge(node a, node b) { return {max(a.m1, b.m1), min(a.m2, b.m2), a.sum + b.sum}; }

void propagate(int n, int nl, int nr) {
    if (lazy[n] == 0 && lazy2[n] == 0) return;
    if (!lazy2[n]) {
        st[n].m1 += lazy[n];
        st[n].m2 += lazy[n];
        st[n].sum += (nr - nl + 1) * lazy[n];
        if (nl != nr) {
            lazy[n * 2] += lazy[n];
            lazy[n * 2 + 1] += lazy[n];
        }
    } else {
        st[n].m1 = st[n].m2 = lazy[n] + lazy2[n];
        st[n].sum = (nr - nl + 1) * (lazy[n] + lazy2[n]);
        if (nl != nr) {
            lazy[n * 2] = lazy[n * 2 + 1] = lazy[n];
            lazy2[n * 2] = lazy2[n * 2 + 1] = lazy2[n];
        }
    }
    lazy[n] = lazy2[n] = 0;
}

void add(int l, int r, int n, int nl, int nr, ll v) {
    propagate(n, nl, nr);
    if (nr < l || r < nl) return;
    if (l <= nl && nr <= r) {
        lazy[n] = v;
        propagate(n, nl, nr);
        return;
    }
    int mid = nl + nr >> 1;
    add(l, r, n * 2, nl, mid, v);
    add(l, r, n * 2 + 1, mid + 1, nr, v);
    st[n] = merge(st[n * 2], st[n * 2 + 1]);
}

void square(int l, int r, int n, int nl, int nr) {
    propagate(n, nl, nr);
    if (nr < l || r < nl) return;
    if (l <= nl && nr <= r) {
        if (floor(sqrt(st[n].m1)) == floor(sqrt(st[n].m2))) {
            lazy2[n] = floor(sqrt(st[n].m1));
            propagate(n, nl, nr);
            return;
        }
        if (st[n].m2 + 1 == st[n].m1) {
            lazy[n] = floor(sqrt(st[n].m1)) - st[n].m1;
            propagate(n, nl, nr);
            return;
        }
    }
    int mid = nl + nr >> 1;
    square(l, r, n * 2, nl, mid);
    square(l, r, n * 2 + 1, mid + 1, nr);
    st[n] = merge(st[n * 2], st[n * 2 + 1]);
}

ll sum(int l, int r, int n, int nl, int nr) {
    propagate(n, nl, nr);
    if (nr < l || r < nl) return 0;
    if (l <= nl && nr <= r) return st[n].sum;
    int mid = nl + nr >> 1;
    return sum(l, r, n * 2, nl, mid) + sum(l, r, n * 2 + 1, mid + 1, nr);
}

int main(void) {
    int T = readInt(), pv = 0;
    while (T--) {
        memset(st, 0, sizeof(st));
        memset(lazy, 0, sizeof(lazy));
        memset(lazy2, 0, sizeof(lazy2));
        int n, q;
        n = readInt();
        q = readInt();
        for (int i = 1; i <= n; ++i) {
            int t = readInt();
            add(i, i, 1, 1, n, t);
        }
        while (q--) {
            int cmd, a, b, x;
            cmd = readInt(), a = readInt(), b = readInt();
            if (cmd == 3) {
                x = readInt();
                add(a, b, 1, 1, n, x);
            } else if (cmd == 1)
                square(a, b, 1, 1, n);
            else
                writeInt(sum(a, b, 1, 1, n), '\n');
        }
    }
    Flusher();

    return 0;
}