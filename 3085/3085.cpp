#include <stdio.h>

int n;
char arr[50][50];

int max(int a, int b) { return a > b ? a : b; }

void swap(char *a, char *b) {
    char t = *a;
    *a = *b;
    *b = t;
}

int max_candy() {
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int t1 = 1, t2 = 1;
            for (int k = i + 1; k < n; ++k) {  // row
                if (arr[i][j] == arr[k][j])
                    t1++;
                else
                    break;
            }
            for (int k = j + 1; k < n; ++k) {  // column
                if (arr[i][j] == arr[i][k])
                    t2++;
                else
                    break;
            }
            ret = max(ret, max(t1, t2));
        }
    }
    return ret;
}

int main(void) {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) scanf(" %c", &arr[i][j]);

    int ans = max_candy();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j + 1 < n && arr[i][j] != arr[i][j + 1]) {
                swap(&arr[i][j], &arr[i][j + 1]);
                ans = max(ans, max_candy());
                swap(&arr[i][j], &arr[i][j + 1]);
            }
            if (i + 1 < n && arr[i][j] != arr[i + 1][j]) {
                swap(&arr[i][j], &arr[i + 1][j]);
                ans = max(ans, max_candy());
                swap(&arr[i][j], &arr[i + 1][j]);
            }
        }
    }
    printf("%d", ans);

    return 0;
}