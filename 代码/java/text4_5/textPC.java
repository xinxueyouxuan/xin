package text4_5;

public class textPC {
    textCPU cpu;
    textHardDisk HD; // 对应题目 UML 图中的变量名 HD

    public void setCPU(textCPU c) {
        this.cpu = c;
    }

    public void setHardDisk(textHardDisk h) {
        this.HD = h;
    }

    public void show() {
        System.out.println("CPU的速度为：" + cpu.getSpeed());
        System.out.println("硬盘的容量为：" + HD.getAmount());
    }
}