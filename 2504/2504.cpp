#include <stdio.h>
#include <string.h>

typedef long long ll;

ll score[100], st[100];
int top1, top2;
char input[100];
char close[] = {' ', '(', ' ', '['};

int main(void) {
    scanf("%s", input);

    int len = strlen(input);
    score[top1++] = 0LL;
    for (int i = 0; i < len; ++i) {
        int c = input[i];
        if (c == '(' || c == '[') {
            st[top2++] = c;
            score[top1++] = 0LL;
        } else {
            if (close[c % 10] != st[top2 - 1]) {
                printf("0");
                return 0;
            }
            --top2;
            ll t = score[--top1];
            ll p = (c == ')' ? 2 : 3);
            if (t == 0) {
                ll s = score[--top1] + p;
                score[top1++] = s;
            } else {
                ll s = score[--top1] + t * p;
                score[top1++] = s;
            }
        }
    }

    if (top2 != 0)
        printf("0");
    else
        printf("%lld", score[top1 - 1]);

    return 0;
}