/*
 * 通讯录管理系统 (C语言实现 - 详细注释版)
 * 功能: 添加、显示、删除、查找、修改、清空、排序、统计联系人
 * 
 * 核心数据结构:
 *   struct person      - 单个联系人信息（姓名、性别、年龄、电话、住址）
 *   struct addressbooks - 通讯录整体（联系人数组 + 当前人数）
 *
 * 设计思路:
 *   使用结构体数组存储联系人，通过size变量记录当前数量，
 *   增删改查都基于数组操作，删除时将后续元素前移。
 */

#include <stdio.h>
#include <stdlib.h>  // 标准库：system("pause"), system("cls")	\\*美化程序*\\ 
#include <string.h>  // 字符串处理：strcmp(比较), strcpy(复制), strlen(求长度), strstr(子串查找)
#include <ctype.h>   // 字符处理：isspace(判断空白字符)

// ==================== 常量定义 ====================
#define MAX         1000    // 通讯录最大容量（最多存储1000个联系人）
#define MAX_NAME    50      // 姓名最大字符数（预留1字节存'\0'，实际可输入49字符）
#define MAX_SEX     10      // 性别最大字符数（"男"/"女"只需3字节，留余量）
#define MAX_PHONE   20      // 电话号码最大字符数（手机号11位，留余量）
#define MAX_ADDR    100     // 家庭住址最大字符数

// ==================== 结构体定义 ====================

/*
 * 单个联系人结构体
 * 包含5个字段：姓名、性别、年龄、电话、住址
 * 其中姓名/性别/电话/住址为字符数组，年龄为整数
 */
struct person {
    char name[MAX_NAME];      
	// 姓名（字符数组，最多MAX_NAME-1个有效字符）
    char sex[MAX_SEX];        
	// 性别（存储"男"或"女"）
    int age;                  
	// 年龄（整数，范围建议0-150）
    char phone[MAX_PHONE];    
	// 电话号码（字符串形式，方便存储座机号如"010-12345678"）
    char address[MAX_ADDR];   
	// 家庭住址
};

/*
 * 通讯录整体结构体
 * personarr[] - 联系人数组，大小固定为MAX
 * size        - 当前已存储的联系人数量（有效数据在数组中的[0, size-1]范围）
 *
 * 重要：size既是计数器，也是下一个新联系人将要存放的位置索引
 * 例如 size=5 表示已有5个联系人(personarr[0]~personarr[4])，新联系人将存入personarr[5]
 */
struct addressbooks {
    struct person personarr[MAX];  
	// 联系人数组（预分配MAX个空间，实际使用size个）
    int size;                      
	// 当前联系人个数（关键变量，所有操作都依赖它）
};

// ==================== 工具函数 ====================

/*
 * 函数: trim
 * 功能: 去除字符串首尾的空白字符（空格、制表符等）
 * 参数: str - 待处理的字符串（原地修改）
 * 
 * 工作原理:
 *   1. 从字符串末尾开始，逐个检查是否为空白字符，是则替换为'\0'
 *   2. 从字符串开头找第一个非空白字符，用memmove将字符串前移
 * 
 * 为什么需要这个函数？
 *   scanf读取字符串时不会自动去除首尾空格（虽然%s跳过前导空白，但可能有多余空格）
 *   用户输入"  张三  "会被清理为"张三"，保证数据整洁
 */
void trim(char *str) {
    int len = strlen(str);  
	// 获取字符串当前长度
    
    // 第一步：从末尾向开头扫描，去掉尾部空白字符
    // 例如 "张三   " -> len=7，最后一个非空格是'三'(索引4)，把索引5位置设为'\0'
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[--len] = '\0';  // 先让len减1，再在该位置放入字符串结束符
    }
    
    // 第二步：从开头向末尾扫描，找到第一个非空白字符的位置
    int start = 0;
    while (str[start] && isspace((unsigned char)str[start])) {
        start++;  // 跳过前导空格
    }
    
    // 第三步：如果有前导空格，使用memmove将字符串整体前移
//***memmove比strcpy安全***，能正确处理内存重叠的情况
    // 例如 "   张三" -> start=3，把"张三"(索引3起)移动到索引0位置
    if (start > 0) {
        memmove(str, str + start, len - start + 1);  
		// +1是为了把'\0'也复制过去
    }
}

/*
 * 函数: showmenu
 * 功能: 在屏幕上打印系统功能菜单
 * 
 * 每次循环都会调用此函数，让用户知道有哪些操作可选
 */
void showmenu() {
    printf("**********************\n");
    printf("*****1.添加联系人*****\n");
    printf("*****2.显示联系人*****\n");
    printf("*****3.删除联系人*****\n");
    printf("*****4.查找联系人*****\n");
    printf("*****5.修改联系人*****\n");
    printf("*****6.清空联系人*****\n");
    printf("*****7.按姓名排序*****\n");
    printf("*****8.统计信息  *****\n");
    printf("*****0.退出通讯录*****\n");
    printf("**********************\n");
}

// ==================== 核心功能函数 ====================

/*
 * 函数: addperson
 * 功能: 向通讯录末尾添加一个新联系人
 * 参数: abs - 通讯录结构体指针（传指针才能修改原结构体的内容）
 * 
 * 执行流程:
 *   1. 检查通讯录是否已满(size == MAX)
 *   2. 如果未满，让用户依次输入姓名、性别、年龄、电话、住址
 *   3. 数据存入 personarr[size] 位置（当前数组末尾）
 *   4. size自增1（为新联系人腾出下一个位置）
 * 
 * 注意事项:
 *   - scanf中使用%49s限制读取长度，防止用户输入超长字符串导致缓冲区溢出
 *   - 每次scanf后用while(getchar()!='\n')清除输入缓冲区的残留换行符
 *   - 年龄超过合理范围(0-150)时自动修正为0
 */
void addperson(struct addressbooks *abs) {
    // ===== 第一步：检查容量上限 =====
    if (abs->size == MAX) {  
	// 当前人数已达最大值
        printf("通讯录已满，无法添加\n");
        return;  
		// 直接返回，不执行后续添加操作
    }
    
    // ===== 第二步：逐个输入联系人信息 =====
    // 当前要添加的位置索引就是size（数组末尾）
    // 例如size=3，已有personarr[0],personarr[1],personarr[2]，新联系人存personarr[3]
    
    // --- 输入姓名 ---
    printf("请输入姓名：\n");
    scanf(" %49s", abs->personarr[abs->size].name);
    //       空格           限制最多读49个字符（留1字节给'\0'）
    // %s前的空格作用：跳过输入缓冲中的所有空白字符（换行、空格等）
    while (getchar() != '\n');  
	// 清空缓冲区剩余内容（重要！避免影响后续输入）
    trim(abs->personarr[abs->size].name);  
	// 去除输入中可能带的空格
    
    // --- 检查同名联系人 ---
    int i, exist = 0;
    for (i = 0; i < abs->size; i++) {  
	// 遍历已有联系人
        // strcmp比较两个字符串，相等返回0
        if (strcmp(abs->personarr[i].name, abs->personarr[abs->size].name) == 0) {
            exist = 1;  
			// 标记找到同名
            break;      
			// 已找到，无需继续循环
        }
    }
    if (exist) {  
	// 存在同名联系人，询问是否继续
        printf("警告：通讯录中已存在同名联系人「%s」，仍要继续添加吗？\n",
               abs->personarr[abs->size].name);
        printf("1 - 继续添加\n其他键 - 取消\n");
        int confirm;
        scanf("%d", &confirm);
        while (getchar() != '\n');
        if (confirm != 1) {
            printf("已取消添加。\n");
            system("pause");
            system("cls");
            return;  
			// 用户取消，直接返回
        }
    }
    
    // --- 输入性别 ---
    printf("请输入性别\n");
    printf("1 男\n");
    printf("2 女\n");
    scanf(" %9s", abs->personarr[abs->size].sex);
    while (getchar() != '\n');
    trim(abs->personarr[abs->size].sex);
    
    // 将用户输入的数字1/2转换为中文"男"/"女"存储
    // 这样显示时更直观，也方便后续统计
    if (strcmp(abs->personarr[abs->size].sex, "1") == 0) {
        strcpy(abs->personarr[abs->size].sex, "男");  
		// 复制"男"覆盖原值
    } else if (strcmp(abs->personarr[abs->size].sex, "2") == 0) {
        strcpy(abs->personarr[abs->size].sex, "女");
        //复制"女"覆盖原值 
    }
    // 如果用户输入了其他内容（如直接输入"男"），保留原样
    
    // --- 输入年龄 ---
    printf("请输入年龄\n");
    scanf("%d", &abs->personarr[abs->size].age);
    //      ↑注意：整数需要取地址符&，因为age是int类型不是数组
    while (getchar() != '\n');
    
    // 校验年龄是否在合理范围内（0-150岁）
    if (abs->personarr[abs->size].age < 0 || abs->personarr[abs->size].age > 150) {
        printf("年龄输入不合法(0~150)，已自动设置为0。\n");
        abs->personarr[abs->size].age = 0;
    }
    
    // --- 输入电话 ---
    printf("请输入联系人电话\n");
    scanf(" %19s", abs->personarr[abs->size].phone);
    while (getchar() != '\n');
    trim(abs->personarr[abs->size].phone);
    
    // --- 输入住址 ---
    printf("请输入家庭住址\n");
    scanf(" %99s", abs->personarr[abs->size].address);
    while (getchar() != '\n');
    trim(abs->personarr[abs->size].address);
    
    // ===== 第三步：更新联系人计数 =====
    abs->size++;  // 联系人数量加1，这个新联系人就正式加入了
    printf("添加成功\n");
    
    system("pause");  // 暂停程序，等待用户按任意键
    system("cls");    // 清屏（Windows命令，为下一次菜单显示做准备）
}

/*
 * 函数: showperson
 * 功能: 以表格形式显示通讯录中所有联系人的完整信息
 * 参数: abs - 通讯录结构体指针（const表示不会修改数据，但这里为了简洁未加）
 * 
 * 显示格式:
 *   +------+--------+------+------+----------+--------+
 *   | 编号 |  姓名  | 性别 | 年龄 |   电话   |  住址  |
 *   +------+--------+------+------+----------+--------+
 *   |  1   | 张三   |  男  |  25  | 138...  | 北京.. |
 *   +------+--------+------+------+----------+--------+
 */
void showperson(struct addressbooks *abs) {
    // 首先检查通讯录是否为空
    if (abs->size == 0) {
        printf("当前记录为空\n");
    } else {
        int i;
        printf("\n========== 共有 %d 位联系人 ==========\n", abs->size);
        
        // 打印表头
        // 每个字段的宽度通过%-数字s控制：负号表示左对齐，数字表示占用宽度
        printf("+------+----------------------+------+------+--------------------+----------------------------+\n");
        printf("| %-4s | %-20s | %-4s | %-4s | %-18s | %-26s |\n",
               "编号", "姓名", "性别", "年龄", "电话", "住址");
        printf("+------+----------------------+------+------+--------------------+----------------------------+\n");
        
        // 逐行打印每个联系人的信息
        for (i = 0; i < abs->size; i++) {
            // i+1 是显示给用户看的编号（从1开始）
            printf("| %4d | %-20s | %-4s | %4d | %-18s | %-26s |\n",
                   i + 1,                          
				   // 编号（右对齐，占4位）
                   abs->personarr[i].name,         
				   // 姓名（左对齐，占20位）
                   abs->personarr[i].sex,          
				   // 性别（左对齐，占4位）
                   abs->personarr[i].age,          
				   // 年龄（右对齐，占4位）
                   abs->personarr[i].phone,        
				   // 电话（左对齐，占18位）
                   abs->personarr[i].address);     
				   // 住址（左对齐，占26位）
        }
        
        // 打印表格底线
        printf("+------+----------------------+------+------+--------------------+----------------------------+\n");
    }
    
    system("pause");
    system("cls");
}

/*
 * 函数: isexist
 * 功能: 根据姓名精确查找联系人（只返回第一个匹配的索引）
 * 参数: abs  - 通讯录结构体指针
 *       name - 要查找的姓名
 * 返回值: 找到返回下标(0~size-1)，未找到返回-1
 * 
 * 查找原理:
 *   遍历personarr[0]到personarr[size-1]，用strcmp比较name字段
 *   strcmp返回值：相等为0，str1>str2为正数，str1<str2为负数
 * 
 * 注意: 如果有多个同名联系人，本函数只返回第一个找到的
 */
int isexist(struct addressbooks *abs, const char *name) {
    int i;
    for (i = 0; i < abs->size; i++) {
        // strcmp比较两个字符串，相等时返回0
        if (strcmp(abs->personarr[i].name, name) == 0) {
            return i;  
			// 找到！返回当前下标，即该联系人的地址 
        }
    }
    return -1;  
	// 遍历完都没找到，返回-1表示不存在
}

/*
 * 函数: findbyphone
 * 功能: 根据电话号码模糊查找（支持部分匹配）
 * 参数: abs   - 通讯录结构体指针
 *       phone - 要查找的电话号码（可以是完整号码或部分号码）
 * 返回值: 找到返回第一个匹配的下标，未找到返回-1
 * 
 * 与isexist的区别:
 *   isexist使用strcmp做精确匹配（必须完全相等）
 *   findbyphone使用strstr做子串匹配（phone只要出现在电话字段中即可）
 * 
 * 使用场景: 用户只记得电话号码的一部分（如后4位），也能找到对应联系人
 */
int findbyphone(struct addressbooks *abs, const char *phone) {
    int i;
    for (i = 0; i < abs->size; i++) {
        // strstr: 在字符串1中查找字符串2，找到返回指向子串的指针，没找到返回NULL
        if (strstr(abs->personarr[i].phone, phone) != NULL) {
            return i;  
			// 电话号码中包含搜索关键词，匹配成功
        }
    }
    return -1;  
	// 所有联系人都没匹配到
}

/*
 * 函数: deleteperson
 * 功能: 根据姓名删除指定联系人
 * 参数: abs - 通讯录结构体指针
 * 
 * 删除原理（数组元素前移法）:
 *   假设size=5，要删除personarr[2]（第3个联系人）
 *   操作: personarr[2] = personarr[3]
 *         personarr[3] = personarr[4]
 *         size--  (变为4)
 *   这样personarr[2]和personarr[3]的内容就是原来的第4、5个联系人
 *   原来的personarr[4]虽然数据还在，但已不在有效范围[0,size-1]内
 * 
 * 安全措施: 
 *   删除前显示联系人详细信息并二次确认，防止误删
 */
void deleteperson(struct addressbooks *abs) {
    printf("请输入要删除的联系人姓名：\n");
    
    char name[MAX_NAME];
    scanf(" %49s", name);
    while (getchar() != '\n');
    
    // 调用isexist查找该姓名
    int ret = isexist(abs, name);
    
    if (ret != -1) {  
	// 找到了该联系人
        // ===== 先显示详细信息，让用户确认 =====
        printf("\n========== 待删除联系人信息 ==========\n");
        printf("姓名：%s\n", abs->personarr[ret].name);
        printf("性别：%s\n", abs->personarr[ret].sex);
        printf("年龄：%d\n", abs->personarr[ret].age);
        printf("电话：%s\n", abs->personarr[ret].phone);
        printf("住址：%s\n", abs->personarr[ret].address);
        printf("=======================================\n");
        printf("确认删除该联系人？(1 - 确认，其他 - 取消): ");
        
        int confirm;
        scanf("%d", &confirm);
        while (getchar() != '\n');
        
        if (confirm == 1) {  
		// 用户确认删除
            // ===== 执行删除：将后续元素依次前移 =====
            int i;
            // 从待删除位置ret开始，将后面的每个元素复制到前一个位置
            // 循环条件 i < abs->size - 1：因为要把personarr[i+1]赋给personarr[i]
            //              如果i=size-1，personarr[i+1]就越界了
            for (i = ret; i < abs->size - 1; i++) {
                abs->personarr[i] = abs->personarr[i + 1];  
				// 整体结构体赋值（C语言支持）
            }
            abs->size--;  
			// 总人数减1（关键！缩小有效数据范围）
            printf("已成功删除联系人「%s」\n", name);
        } else {
            printf("已取消删除\n");
        }
    } else {
        printf("查无此人\n");  
		// isexist返回-1，没找到
    }
}

/*
 * 函数: findperson
 * 功能: 查找联系人（支持按姓名精确查找和按电话号码模糊查找）
 * 参数: abs - 通讯录结构体指针
 * 
 * 两种查找模式:
 *   1. 按姓名：调用isexist，精确匹配整个姓名字段
 *   2. 按电话：调用findbyphone，电话号码中包含输入内容即匹配
 */
void findperson(struct addressbooks *abs) {
    int choice;
    printf("请选择查找方式：\n");
    printf("1 - 按姓名查找（精确匹配）\n");
    printf("2 - 按电话号码查找（模糊匹配，输入部分号码即可）\n");
    printf("请输入选择：");
    scanf("%d", &choice);
    while (getchar() != '\n');
    
    if (choice == 1) {  
	// 按姓名查找
        printf("请输入您要查找的联系人姓名：\n");
        char name[MAX_NAME];
        scanf(" %49s", name);
        while (getchar() != '\n');
        
        int ret = isexist(abs, name);  
		// 精确查找
        
        if (ret != -1) {  // 找到了
            printf("========== 联系人信息 ==========\n");
            printf("姓名：%s\n", abs->personarr[ret].name);
            printf("性别：%s\n", abs->personarr[ret].sex);
            printf("年龄：%d\n", abs->personarr[ret].age);
            printf("电话：%s\n", abs->personarr[ret].phone);
            printf("住址：%s\n", abs->personarr[ret].address);
        } else {
            printf("查无此人\n");
        }
    } else if (choice == 2) {  
	// 按电话号码模糊查找
        printf("请输入要查找的电话号码（可输入部分号码，如后4位）：\n");
        char phone[MAX_PHONE];
        scanf(" %19s", phone);
        while (getchar() != '\n');
        
        int ret = findbyphone(abs, phone);  
		// 模糊查找
        
        if (ret != -1) {
            printf("========== 找到匹配的联系人 ==========\n");
            printf("姓名：%s\n", abs->personarr[ret].name);
            printf("性别：%s\n", abs->personarr[ret].sex);
            printf("年龄：%d\n", abs->personarr[ret].age);
            printf("电话：%s\n", abs->personarr[ret].phone);
            printf("住址：%s\n", abs->personarr[ret].address);
        } else {
            printf("未找到包含该号码的联系人\n");
        }
    } else {
        printf("无效选择\n");
    }
    
    system("pause");
    system("cls");
}

/*
 * 函数: modifyperson
 * 功能: 修改指定联系人的信息
 * 参数: abs - 通讯录结构体指针
 * 
 * 设计特点:
 *   修改前先显示当前值，方便用户对比
 *   对于字符串字段：直接回车跳过表示保留原值
 *   对于年龄：输入负数保留原值
 *   对于性别：输入1/2修改，输入其他保留原值
 * 
 * 这样设计的好处：用户只想改电话号码时，不需要重新输入其他所有字段
 */
void modifyperson(struct addressbooks *abs) {
    printf("输入你要修改的联系人姓名：\n");
    
    char name[MAX_NAME];
    scanf(" %49s", name);
    while (getchar() != '\n');
    
    int ret = isexist(abs, name);  
	// 先查找该联系人
    
    if (ret != -1) {  // 找到了
        // ===== 先显示当前所有信息 =====
        printf("\n========== 当前信息 ==========\n");
        printf("姓名：%s\n", abs->personarr[ret].name);
        printf("性别：%s\n", abs->personarr[ret].sex);
        printf("年龄：%d\n", abs->personarr[ret].age);
        printf("电话：%s\n", abs->personarr[ret].phone);
        printf("住址：%s\n", abs->personarr[ret].address);
        printf("==============================\n");
        printf("（提示：直接回车可保留原值，年龄输入负数保留原值）\n");
        
        char temp[MAX_ADDR];  
		// 临时缓冲区，用于接收用户输入
        int newAge;
        
        // --- 修改姓名 ---
        printf("请输入修改后的姓名：\n");
        scanf(" %49s", temp);
        while (getchar() != '\n');
        if (strlen(temp) > 0) {  
		// 用户输入了内容（非空）
            trim(temp);
            strcpy(abs->personarr[ret].name, temp);  
			// 覆盖原姓名
        }
        // 如果用户直接回车，temp为空字符串，不修改原值
        
        // --- 修改性别 ---
        printf("请输入修改后的性别\n");
        printf("1.男\n");
        printf("2.女\n");
        printf("其他键保留原值\n");
        int sexChoice;
        scanf("%d", &sexChoice);
        while (getchar() != '\n');
        if (sexChoice == 1) {
            strcpy(abs->personarr[ret].sex, "男");  
			// 直接覆盖
        } else if (sexChoice == 2) {
            strcpy(abs->personarr[ret].sex, "女");
        }
        // 输入其他数字保留原值
        
        // --- 修改年龄 ---
        printf("请输入修改后的年龄（输入负数保留原值）\n");
        scanf("%d", &newAge);
        while (getchar() != '\n');
        if (newAge >= 0) {  
		// 输入非负数才修改
            if (newAge > 150) {
                printf("年龄超出合理范围(>150)，保留原值\n");
            } else {
                abs->personarr[ret].age = newAge;  
				// 更新年龄
            }
        }
        
        // --- 修改电话 ---
        printf("请输入修改后的电话\n");
        scanf(" %19s", temp);
        while (getchar() != '\n');
        if (strlen(temp) > 0) {  
		// 输入了内容才修改
            trim(temp);
            strcpy(abs->personarr[ret].phone, temp);
        }
        
        // --- 修改住址 ---
        printf("请输入修改后的住址\n");
        scanf(" %99s", temp);
        while (getchar() != '\n');
        if (strlen(temp) > 0) {  
		// 输入了内容才修改
            trim(temp);
            strcpy(abs->personarr[ret].address, temp);
        }
        
        printf("修改成功!\n");
    } else {
        printf("查无此人\n");
    }
    
    system("pause");
    system("cls");
}

/*
 * 函数: sortperson
 * 功能: 按姓名字段对联系人数组进行升序排序
 * 参数: abs - 通讯录结构体指针
 * 
 * 排序算法: 冒泡排序（Bubble Sort）
 *   时间复杂度: O(n2)，对于通讯录这种数据量不大的场景足够
 *   空间复杂度: O(1)，原地排序
 * 
 * 排序原理:
 *   外层循环控制比较轮数（n-1轮）
 *   内层循环进行相邻元素比较和交换
 *   每轮将当前未排序部分的最大值"冒泡"到最后
 * 
 * strcmp比较规则:
 *   按字典序比较，中文在ASCII扩展字符集中按编码顺序排列
 *   返回值>0表示str1在字典序中排在str2之后（需要交换）
 */
void sortperson(struct addressbooks *abs) {
    if (abs->size <= 1) {
        printf("通讯录中联系人不足2位，无需排序\n");
        return;  
		// 少于2人，没有排序的必要
    }
    
    int i, j;
    struct person temp;  
	// 用于交换的临时变量
    
    // 外层循环：控制比较轮数
    // size=5时需要比较4轮（i从0到3）
    for (i = 0; i < abs->size - 1; i++) {
        // 内层循环：相邻元素两两比较
        // j的范围逐渐缩小，因为每轮结束后最后i个元素已排好序
        for (j = 0; j < abs->size - 1 - i; j++) {
            // 如果前一个元素的姓名比后一个"大"（字典序靠后），则交换
            if (strcmp(abs->personarr[j].name, abs->personarr[j+1].name) > 0) {
                // 交换两个完整的结构体（C语言允许结构体直接赋值）
                temp = abs->personarr[j];
                abs->personarr[j] = abs->personarr[j+1];
                abs->personarr[j+1] = temp;
            }
        }
    }
    printf("按姓名排序完成！\n");
}

/*
 * 函数: statistics
 * 功能: 统计并显示通讯录的各项数据指标
 * 参数: abs - 通讯录结构体指针
 * 
 * 统计内容:
 *   1. 总人数
 *   2. 性别分布：男性/女性人数及百分比
 *   3. 年龄统计：平均年龄、最小年龄、最大年龄
 *   4. 年龄段分布：未成年(<18)、中青年(18-60)、老年(>60)
 * 
 * 百分比计算: (部分人数 / 总人数) * 100，保留1位小数
 * 注意类型转换: 整型除法会截断小数，需要先转为float
 */
void statistics(struct addressbooks *abs) {
    if (abs->size == 0) {
        printf("通讯录为空，无法统计\n");
        system("pause");
        system("cls");
        return;
    }
    
    int i;
    
    int maleCount = 0, femaleCount = 0, otherCount = 0;  
	// 性别计数器
    int totalAge = 0;        
	// 年龄总和（用于计算平均值）
    int minAge = 999, maxAge = -1;  
	// 最值年龄（初始值：min设极大，max设极小）
    int youngCount = 0, middleCount = 0, oldCount = 0;   
	// 年龄段计数器
    
    // ===== 遍历所有联系人，累计统计数据 =====
    for (i = 0; i < abs->size; i++) {
        // --- 性别统计 ---
        if (strcmp(abs->personarr[i].sex, "男") == 0) {
            maleCount++;     
			// 男性人数+1
        } else if (strcmp(abs->personarr[i].sex, "女") == 0) {
            femaleCount++;   
			// 女性人数+1
        } else {
            otherCount++;    
			// 性别不是"男"或"女"的归为其他
        }
        
        // --- 年龄累计 ---
        totalAge += abs->personarr[i].age;  
		// 累加年龄
        
        // --- 最值更新 ---
        if (abs->personarr[i].age < minAge) {
            minAge = abs->personarr[i].age;  
			// 发现更小的年龄，更新最小值
        }
        if (abs->personarr[i].age > maxAge) {
            maxAge = abs->personarr[i].age;  
			// 发现更大的年龄，更新最大值
        }
        
        // --- 年龄段统计 ---
        if (abs->personarr[i].age < 18) {
            youngCount++;    
			// 未成年人
        } else if (abs->personarr[i].age <= 60) {
            middleCount++;   
			// 18-60岁中青年
        } else {
            oldCount++;      
			// 60岁以上老年人
        }
    }
    
    // ===== 输出统计结果 =====
    printf("\n========== 通讯录统计信息 ==========\n");
    printf("总人数：%d 人\n", abs->size);
    
    // 性别分布
    printf("\n--- 性别分布 ---\n");
    printf("男性：%d 人 (%.1f%%)\n", maleCount, 
           100.0 * maleCount / abs->size);   
		   // 乘以100.0确保浮点运算
    printf("女性：%d 人 (%.1f%%)\n", femaleCount, 
           100.0 * femaleCount / abs->size);
    if (otherCount > 0) {  
	// 只有存在"其他"性别时才显示
        printf("其他：%d 人 (%.1f%%)\n", otherCount, 
               100.0 * otherCount / abs->size);
    }
    
    // 年龄统计
    printf("\n--- 年龄分布 ---\n");
    printf("平均年龄：%.1f 岁\n", (float)totalAge / abs->size);  
		// 强制转换为float避免整除
    printf("最小年龄：%d 岁\n", minAge);
    printf("最大年龄：%d 岁\n", maxAge);
    
    // 年龄段分布
    printf("未成年(<18岁)：%d 人 (%.1f%%)\n", youngCount, 
           100.0 * youngCount / abs->size);
    printf("中青年(18-60岁)：%d 人 (%.1f%%)\n", middleCount, 
           100.0 * middleCount / abs->size);
    printf("老年(>60岁)：%d 人 (%.1f%%)\n", oldCount, 
           100.0 * oldCount / abs->size);
    printf("====================================\n");
    
    system("pause");
    system("cls");
}

/*
 * 函数: cleanperson
 * 功能: 清空通讯录中的所有联系人
 * 参数: abs - 通讯录结构体指针
 * 
 * 实现原理:
 *   不需要真正删除数组中的数据（逐个清零太耗时）
 *   直接将size设为0即可，这样所有操作都会认为通讯录为空
 *   旧数据虽然还在内存中，但添加新联系人时会覆盖
 * 
 * 安全措施:
 *   清空前需要输入当前联系人数量作为确认码
 *   这样可以有效防止误操作（按错菜单导致的清空）
 */
void cleanperson(struct addressbooks *abs) {
    if (abs->size == 0) {
        printf("通讯录已为空，无需清空\n");
    } else {
        // 显示警告信息
        printf("??  警告：您即将清空所有 %d 位联系人！\n", abs->size);
        printf("此操作不可恢复！\n");
        // 要求用户输入当前联系人数量以确认（防止误操作）
        printf("请输入当前联系人数量 %d 以确认清空：", abs->size);
        int confirm;
        scanf("%d", &confirm);
        while (getchar() != '\n');
        
        if (confirm == abs->size) {  
		// 输入数字与当前人数一致才执行
            abs->size = 0;  
			// 核心操作：将计数归零
            printf("通讯录已清空\n");
        } else {
            printf("输入不匹配，已取消清空操作\n");
        }
    }
}

/*
 * 函数: main
 * 功能: 程序入口，主控制循环
 * 
 * 程序执行流程:
 *   1. 初始化通讯录（size=0）
 *   2. 进入无限循环：
 *      a. 显示菜单
 *      b. 读取用户选择
 *      c. 根据选择调用对应的功能函数
 *      d. 如果选择0，退出循环，程序结束
 * 
 * 为什么用while(1)无限循环？
 *   通讯录系统应该持续运行，直到用户主动选择退出
 *   每次操作完成后回到菜单，方便进行下一个操作
 */
int main() {
    // ===== 初始化通讯录 =====
    struct addressbooks abs;  // 创建通讯录结构体变量
    abs.size = 0;             // 初始化人数为0（关键！不初始化会有随机值）
    
    int select = 0;           // 存储用户选择的菜单编号
    
    printf("欢迎使用通讯录管理系统！\n");
    
    // ===== 主控制循环 =====
    while (1) {  // 无限循环，只有选择退出(return 0)才会结束
        showmenu();  // 每次循环先打印菜单
        
        // ----- 读取用户选择（带输入验证）-----
        printf("请选择模式（输入数字）\n");
        // scanf返回值：成功读取的参数个数。这里期望返回1（成功读取1个整数）
        if (scanf("%d", &select) != 1) {
            // 用户输入了非数字（如字母），scanf读取失败
            printf("输入无效，请重新输入数字\n");
            while (getchar() != '\n');  // 清空错误输入,即清空缓存区 
            system("pause");
            system("cls");
            continue;  
			// 跳过本次循环，重新显示菜单让用户输入
        }
        // 成功读取整数后，清除缓冲区中残留的换行符
        while (getchar() != '\n');

        // ===== 根据用户选择执行对应功能 =====
        switch (select) {
            case 0:  // 退出系统
                // 退出前二次确认，防止误触
                printf("确认退出？(1 - 确认，其他 - 取消): ");
                int exitConfirm;
                scanf("%d", &exitConfirm);
                while (getchar() != '\n');
                if (exitConfirm == 1) {
                    printf("欢迎下次使用\n");
                    return 0;  
					// 从main函数返回，程序结束
                } else {
                    printf("已取消退出\n");
                    system("pause");
                    system("cls");
                }
                break;  
				// break跳出switch，回到while循环

            case 1: 
			// 添加联系人
                addperson(&abs);  
                // 传入abs的地址（&abs），函数内部通过指针修改原结构体
                break;

            case 2:  
			// 显示所有联系人
                showperson(&abs);
                break;

            case 3:  
			// 删除联系人
                deleteperson(&abs);
                system("pause");
                system("cls");
                break;

            case 4:  
			// 查找联系人（支持姓名和电话两种方式）
                findperson(&abs);
                break;

            case 5:  
			// 修改联系人信息
                modifyperson(&abs);
                break;

            case 6:  
			// 清空通讯录
                cleanperson(&abs);
                system("pause");
                system("cls");
                break;

            case 7:  
			// 按姓名排序
                sortperson(&abs);
                system("pause");
                system("cls");
                break;

            case 8:  
			// 显示统计信息
                statistics(&abs);
                break;

            default:  
			// 输入了0-8以外的数字
                printf("无效选项，请输入0-8之间的数字\n");
                system("pause");
                system("cls");
                break;
        }
        /*
         * switch执行完毕，本轮循环结束
         * 程序会回到while(1)的开头，重新显示菜单
         * 这样用户就可以进行下一个操作了
         */
    }

    // 理论上程序不会执行到这里（while(1)是无限循环，通过return退出）
    // 但为了代码完整性，保留这行
    system("pause");
    return 0;
}
