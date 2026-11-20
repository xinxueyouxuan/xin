package text4_6;

// 1. 定义一个学生类 Student
class Student {
    // 成员变量：姓名 name、年龄 age、分数 score
    String name;
    int age;
    double score; // 分数通常可能带有小数，所以用 double 类型

    // 成员方法：showInfo() 打印学生所有信息
    public void showInfo() {
        System.out.println("姓名：" + name + "，年龄：" + age + "，分数：" + score);
    }
}

// 主类
class Main {
    public static void main(String[] args) {
        // 2. 在主类中创建 2 个学生对象
        Student stu1 = new Student();
        Student stu2 = new Student();

        // 3. 分别给两个对象赋值
        // 给第一个学生赋值
        stu1.name = "张三";
        stu1.age = 20;
        stu1.score = 95.5;

        // 给第二个学生赋值
        stu2.name = "李四";
        stu2.age = 19;
        stu2.score = 88.0;

        // 4. 调用方法输出学生完整信息
        System.out.println("--- 学生 1 的信息 ---");
        stu1.showInfo();

        System.out.println("--- 学生 2 的信息 ---");
        stu2.showInfo();
    }
}