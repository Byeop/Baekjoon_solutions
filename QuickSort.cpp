#include <bits/stdc++.h>

using namespace std;

void qSort(int a[], int l, int r) {
    if (l >= r) return;

    int pivot = l;
    int i = l + 1, j = r;
    while (i <= j) {
        while (i <= r && a[pivot] >= a[i]) ++i;
        while (j > l && a[pivot] <= a[j]) --j;
        if (i > j)
            swap(a[pivot], a[j]);
        else
            swap(a[i], a[j]);
    }

    qSort(a, l, j - 1);
    qSort(a, i, r);
}

int main(void) {
    int a[] = {3, 6, 3, 12, 345, 345, 346, 2345, 123, 2, 2};
    qSort(a, 0, sizeof(a) / sizeof(int) - 1);
    for (int i = 0; i < sizeof(a) / sizeof(int); ++i) printf("%d ", a[i]);

    return 0;
}