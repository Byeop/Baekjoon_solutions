#include <bits/stdc++.h>

using namespace std;

unsigned int arr[30][30];

int main(void) {
    for (int i = 0; i < 26; ++i)
        for (int j = 0; j < 26; ++j) arr[i][j] = 1e9;
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        char input[30];
        scanf(" %[^\n]", input);
        int u = input[0] - 'a';
        int v = input[strlen(input) - 1] - 'a';
        arr[u][v] = 1;
    }

    for (int k = 0; k < 26; ++k)
        for (int i = 0; i < 26; ++i)
            for (int j = 0; j < 26; ++j)
                arr[i][j] = min(arr[i][j], arr[i][k] + arr[k][j]);

    scanf("%d", &m);
    while (m--) {
        char input[30];
        scanf(" %[^\n]", input);
        int u = input[0] - 'a';
        int v = input[strlen(input) - 1] - 'a';
        printf("%c\n", arr[u][v] != 1e9 ? 'T' : 'F');
    }

    return 0;
}