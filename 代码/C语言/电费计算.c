#include <stdio.h>

int main() {
    int a;
    double b = 0.0;
    scanf("%d", &a);
    
    if (a <= 150) {
        b = a * 0.4463;}
	else if (a <= 400) {
        b = 150 * 0.4463 + (a - 150) * 0.4663;}
	else {
        b= 150 * 0.4463 + 250 * 0.4663 + (a - 400) * 0.5663;}
    printf("%.1f\n", b);
    return 0;
}
