#include <algorithm>
#include <cstdio>

int a[20010];

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", a + i);

    std::sort(a, a + n);
    printf("%d", a[n / 2 - !(n % 2)]);

    return 0;
}