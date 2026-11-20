/*
链接：https://ac.nowcoder.com/acm/contest/143768/D
来源：牛客网

题目描述 
学院只有一间学生活动室，本学期共有 n 个社团提交了使用申请。第 i 个申请占用从时刻 lᵢ 到时刻 rᵢ 的时间段（保证 rᵢ > lᵢ）。
管理员发现申请数量远远超过这间活动室的实际容量，只能批准其中一部分。批准时需要满足：同一时刻活动室里只能有一个社团在活动；如果前一场活动在时刻 t 结束，那么下一场活动最早可以从时刻 t 开始——也就是说，两场活动首尾相接是允许的。
请你帮管理员算一算，最多能批准多少个申请。

输入描述:
第一行一个整数 n。
接下来 n 行，每行两个整数 lᵢ, rᵢ，表示第 i 个申请占用时间段的起止时刻。

输出描述:
输出一行一个整数，表示最多能批准的申请数量。

示例1
输入
5
1 2
2 3
1 3
3 4
5 6
输出
4
说明
可以依次批准 (1,2)、(2,3)、(3,4)、(5,6) 四个申请：前一场在 2、3、4 时刻结束，后一场恰好在同一时刻开始，不冲突。若先批准 (1,3)，则最多只能再批准 (3,4)、(5,6)，共 3 个。

备注:
1 ≤ n ≤ 10⁵，0 ≤ lᵢ < rᵢ ≤ 10⁹。
*/
#include <stdio.h>
int main(void){
    long n;
    scanf("%ld",&n);
    long arr[n][2];
    
    for(long i=0;i<n;i++)
        scanf("%ld %ld",&arr[i][0],&arr[i][1]);
    
    for(long i=0;i<n-1;i++)
        for(long j=0;j<n-1-i;j++)
            if(arr[j][1]>arr[j+1][1]){
                long temp0=arr[j][0];
                long temp1=arr[j][1];
                arr[j][0]=arr[j+1][0];
                arr[j][1]=arr[j+1][1];
                arr[j+1][0]=temp0;
                arr[j+1][1]=temp1;
            }

    long count=1;
    long end=arr[0][1];
    for(long i=1;i<n;i++){
        if(arr[i][0]>=end){
            count++;
            end=arr[i][1];
        }
    }
    printf("%ld\n",count);

    return 0;
}