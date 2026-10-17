#include <stdio.h>
// 计算最大公约数    函数
int gcd(int a, int b) {
    // 使用辗转相除法求最大公约数
    while (b != 0) {
        int t = b;  // 临时保存b的值
        b = a % b;     // 计算余数
        a = t;}      // 更新a为原来的b
    return a;}  // 当b为0时，a就是最大公约数
int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    // 找出斜边（最大值）
    int x = a;                  // 先假设a是斜边
    if (b > x) x = b;  // 如果b更大，更新斜边为b
    if (c > x) x = c;  // 如果c更大，更新斜边为c

    //找出最短的直角边（最小值）
    int y = a;         // 先假设a是最短边
    if (b < y) y = b;  // 如果b更小，更新最短边为b
    if (c < y) y = c;  // 如果c更小，更新最短边为c
    int m = y;    // 分子是最短直角边
    int n = x; // 分母是斜边
    // 求分子和分母的最大公约数
    int g = gcd(m, n);
    // 用最大公约数约分
    m /= g;
    n /= g;
    // 步骤5：输出约分后的分数形式
    printf("%d/%d\n", m, n);
    return 0;
}
