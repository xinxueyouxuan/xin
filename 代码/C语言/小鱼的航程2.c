#include <stdio.h>

int main(void) {
    int x, n, w, d, s;
    scanf("%d %d", &x, &n);
    
    w = n / 7;   // 完整周数
    d = n % 7;   // 剩余天数
    
    // 计算剩余天数中包含的周末天数
    int start = x;
    int end = (x + d - 1) % 7;  // 剩余天数的最后一天（转换为1-7）
    if (end == 0) end = 7;
    
    int weekend = 0;
    // 判断剩余天数是否包含周六（6）
    if ((start <= 6 && end >= 6) || (start > 6 && end < 6)) weekend++;
    // 判断剩余天数是否包含周日（7）
    if ((start <= 7 && end >= 7) || (start > 7 && end < 7)) weekend++;
    
    // 总距离 = 完整周距离 + 剩余工作日距离
    s = w * 5 * 250 + (d - weekend) * 250;
    printf("%d", s);
    
    return 0;
}

