package text4_5;

public class Text {
    public static void main(String[] args) {
        // (1) 创建 CPU 对象
        textCPU cpu = new textCPU();
        cpu.setSpeed(2200);

        // (2) 创建 HardDisk 对象
        textHardDisk disk = new textHardDisk();
        disk.setAmount(200);

        // (3) 创建 PC 对象
        textPC pc = new textPC();

        // (4) 组装 CPU
        pc.setCPU(cpu);

        // (5) 组装 HardDisk
        pc.setHardDisk(disk);

        // (6) 显示信息
        pc.show();
    }
}