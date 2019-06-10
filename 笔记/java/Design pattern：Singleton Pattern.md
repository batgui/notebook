# 单例设计模式

```
Ensure a class has only one instance, and provide a global point of access to it.
```

单例设计模式是指某个类在整个系统中只能有一个实例对象可以被获取和使用的代码模式。

单例设计模式要求某个类只能有一个实例，并且系统的其他部分可以使用这个实例。

单例设计模式分为饿汉式和懒汉式

## 饿汉式：

### 1. 直接实例化

注意:要将构造参数私有化
```java
public class Singleton1 {
    private static Singleton1 ourInstance = new Singleton1();

    public static Singleton1 getInstance() {
        return ourInstance;
    }

    private Singleton1() {
    }
}
```

在主函数里面用getInstance()方法来访问SIngleton1的实例。

```java
public class TestSingleton1 {
    public static void main(String[] args) {
        Singleton1 s = Singleton1.getInstance();
        System.out.println(s);
    }
}

```

### 2. 枚举

```java
public enum Singleton2 {
    INSTANCE
}

```

### 3. 静态代码块

```java
public class Singleton3 {
    private static Singleton3 ourInstance;
    static {
        ourInstance = new Singleton3();

    }
    public static Singleton3 getInstance() {
        return ourInstance;
    }

    private Singleton3() {
    }
}

```

饿汉式在类初始化的时候直接new一个对象，不存在线程安全问题。

## 懒汉式：

### 在方法里面创建对象

```java
public class Singleton4 {
    private static Singleton4 ourInstance;

    public static Singleton4 getInstance() {
        if (ourInstance == null) {
            ourInstance = new Singleton4();
        }
        return ourInstance;
    }

    private Singleton4() {
    }
}
```

但是上面这行代码不是线程安全的，若两个线程同时调用getInstance()方法，都判断ourInstance为null，则两个线程会分别创建一个Singleton4对象。

我们可以给getInstance函数体包在synchronized块内，就实现了线程安全的。

```java

    public static Singleton4 getInstance() {
		synchronized(ourInstances) {

	        if (ourInstance == null) {
	            ourInstance = new Singleton4();
	        }
        }
        return ourInstance;
    }
```

### 在内部类被加载和初始化时创建对象

静态内部类不会随着外部类的加载和初始化而初始化，它是要单独去加载和初始化的。

因为是在内部类加载和初始化时创建的，所以是线程安全的。

```java
public class Singleton5 {
    private static Singleton5 ourInstance;

    private static class Inner {
    	private static Singleton5 ourInstance = new Singleton5();
    }
    public static Singleton5 getInstance() {

        return Inner.ourInstance;
    }

}
```