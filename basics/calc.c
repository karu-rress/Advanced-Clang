#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strcalc(const char *str);

int main(void) {
    char string[100];
    int n;

    puts("20 + 5 등 수식 입력 (+-*/)");
    gets_s(string, sizeof string);

    n = strcalc(string);
    printf("%s = %d\n", string, n);
}

int strcalc(const char *str) {
    const char *op = "+-*/";
    int pos, n1, n2;

    pos = strcspn(str, op);
    n1 = atoi(str);
    n2 = atoi(str + pos + 1);

    switch (str[pos]) {
        case '+': return n1 + n2;
        case '-': return n1 - n2;
        case '*': return n1 * n2;        
        case '/': return n1 / n2;                
    }

    return 0;
}