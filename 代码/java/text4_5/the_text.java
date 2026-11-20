package text4_5;

public class the_text {

    public static void main(String[] args) {
        // (1) 创建一个 CPU 对象 cpu，设置 speed 为 2200
        CPU cpu = new CPU();
        cpu.setSpeed(2200);

        // (2) 创建一个 HardDisk 对象 disk，设置 amount 为 200
        HardDisk disk = new HardDisk();
        disk.setAmount(200);

        // (3) 创建一个 PC 对象 pc
        PC pc = new PC();

        // (4) pc 调用 setCPU 方法，实参是 cpu
        pc.setCPU(cpu);

        // (5) pc 调用 setHardDisk 方法，实参是 disk
        pc.setHardDisk(disk);

        // (6) pc 调用 show 方法
        pc.show();
    }
}

// 将这三个类移出主类，或者像下面这样定义为静态内部类
class CPU {
    private int speed;

    // 题目要求：getSpeed() 返回 speed 的值 (返回类型应为 int)
    public int getSpeed() {
        return speed;
    }

    // 题目要求：setSpeed(int m) 将参数 m 赋给 speed
    public void setSpeed(int m) {
        this.speed = m;
    }
}

class HardDisk {
    private int amount;

    // 题目要求：getAmount() 返回 amount 的值 (返回类型应为 int)
    public int getAmount() {
        return amount;
    }

    // 题目要求：setAmount(int m) 将参数 m 赋给 amount
    public void setAmount(int m) {
        this.amount = m;
    }
}

class PC {
    CPU cpu;       // 关联 CPU 类
    HardDisk HD;   // 关联 HardDisk 类，题目 UML 图中变量名是 HD

    // 题目要求：setCPU(CPU c)
    public void setCPU(CPU c) {
        this.cpu = c;
    }

    // 题目要求：setHardDisk(HardDisk h)
    public void setHardDisk(HardDisk h) {
        this.HD = h;
    }

    // 题目要求：show() 方法能显示 CPU 的速度和硬盘的容量
    public void show() {
        // 这里调用 CPU 和 HardDisk 的 get 方法获取数据，并在这里统一打印
        System.out.println("CPU的速度为：" + cpu.getSpeed());
        System.out.println("硬盘的容量为：" + HD.getAmount());
    }
}