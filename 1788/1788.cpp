#include <math.h>
#include <stdio.h>

int fibo[1000010];

int main(void) {
    int n;
    scanf("%d", &n);

    fibo[0] = 0;
    fibo[1] = 1;
    for (int i = 2; i <= 1000000; ++i) fibo[i] = (fibo[i - 1] + fibo[i - 2]) % 1000000000;

    printf("%d\n%d", (n == 0 ? 0 : (n < 0 && n % 2 == 0 ? -1 : 1)), fibo[abs(n)]);

    return 0;
}