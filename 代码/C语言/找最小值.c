#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    scanf("%d", &a[0]);
    int min = a[0];
    for (int i = 1; i < n; i++) {
        scanf("%d", &a[i]);
        if (a[i]< min) {
            min= a[i];
        }
    }
    printf("%d\n", min);
    return 0;
}
