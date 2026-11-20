package text5_5;

abstract class Animal {
    abstract void cry(); 
    abstract String getAnimalName(); 
}

class Dog extends Animal {
    void cry() {
        System.out.println("汪汪汪...");
    }

    String getAnimalName() {
        return "狗";
    }
}

class Cat extends Animal {
    void cry() {
        System.out.println("喵喵喵...");
    }

    String getAnimalName() {
        return "猫";
    }
}

class Simulator {
    public void playSound(Animal animal) {
        System.out.print("现在播放" + animal.getAnimalName() + "的声音：");
        animal.cry();
    }
    String getAnimalName(Animal animal) {
        return animal.getAnimalName();
    }
}

public class text5_5 {
    public static void main(String[] args) {
        Simulator simulator = new Simulator();

        simulator.playSound(new Dog());
        String name = simulator.getAnimalName(new Dog());
        System.out.println("动物的名称是：" + name);

        simulator.playSound(new Cat());
        String name1 = simulator.getAnimalName(new Cat());
        System.out.println("动物的名称是：" + name1);
    }
}