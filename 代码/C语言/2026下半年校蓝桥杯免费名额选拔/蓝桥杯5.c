/*
时间限制：C/C++/Rust/Pascal 1秒，其他语言2秒
空间限制：C/C++/Rust/Pascal 256 M，其他语言512 M
64bit IO Format: %lld
题目描述 
校运会开幕前，后勤处采购了 n 根钢管，第 i 根长 aᵢ 厘米，准备用来搭建看台支架。
施工队需要 k 段长度完全相同的短钢管。每根长钢管可以按需要切成若干段，切剩的边角料直接报废，不同长钢管之间不能拼接。为了让支架用料更宽裕，施工队希望切出来的短钢管尽量长。
请你算出：在能够凑够 k 段短钢管的前提下，单段的最大长度是多少；如果连 1 厘米长的段都凑不够 k 段，则输出 0。

输入描述:
第一行两个整数 n, k，用一个空格分隔。
第二行 n 个正整数 aᵢ，依次为各根钢管的长度，相邻两数之间用一个空格分隔。

输出描述:
输出一行一个整数，表示能切出的等长短钢管的最大长度。

示例1
输入
3 7
10 24 15
输出
6
说明
若单段取 6 厘米，三根钢管分别能切出 1、4、2 段，合计 7 段，正好满足；若单段取 7 厘米，只能切出 1+3+2 = 6 段，不足 7 段。因此最大长度为 6。

备注:
1 ≤ n ≤ 10⁵，1 ≤ k ≤ 10⁹，1 ≤ aᵢ ≤ 10⁹。
*/
#include <stdio.h>

int main(void){
    long n,k,length,sum=0;
    scanf("%ld %ld",&n,&k);
    long a[n];
    
    for(long i=0;i<n;i++)
        scanf("%ld",&a[i]);
    
    long left=1,right=1000000000;
    while(left<=right){
        length=(left+right)/2;
        sum=0;
        for(long i=0;i<n;i++)
            sum+=a[i]/length;
        
        if(sum>=k)
            left=length+1;
        else
            right=length-1;
    }
    printf("%ld",length);
    
    return 0;
}