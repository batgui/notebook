spring 体系结构：

Core container核心容器。是spring IOC部分，再上面试AOP部分，Data Access 是持久成的解决方案 ，web里面有websocket，和servlet，springMVC。最底下是单元测试

Core Container

JDBC 连接Mysql数据库执行操作代码块
```java
    public static void main(String[] args) throws Exception{
        //DriverManager.registerDriver(new com.mysql.jdbc.Driver());
        Class.forname("new com.mysql.jdbc.Driver")
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/store", "root","123");
        PreparedStatement pstm = conn.prepare Statement("select * from account");
        ResultSet rs = pstm.executeQuery() ;
        while(rs.next()) {
            System.out.println(rs.getString("id"));

        }
        rs.close();
        pstm.close();
        conn.close();
    }
```
程序的耦合(程序间的依赖关系)
1. 类之间的依赖
2. 方法间的依赖

降低程序间的依赖关系，做到编译器不依赖，运行时依赖

解耦的思路:
1. 使用反射来创建对象，避免使用new关键字
2. 通过读取配置文件来获取要创建对象的全限定类名（唯一标识=全限定类名keyvalue）
配置文件可以是xml，也可以是properties
业务层调用持久层

表现层 --> 业务层 --> 持久层
```java
public class BeanFactory {
    private  static Properties props;
    static {
        try {
            props = new Properties();
            //获取properties文件的流对象
            InputStream in = BeanFactory.class.getClassLoader().getResourceAsStream("bean.properties");
            props.load(in);
        }catch (Exception e) {
            throw new ExceptionInInitializerError("Initialize properties error");

        }
    }
    public static Object getBean(String beanName) {
        Object bean = null;
        try {
            String beanPath = props.getProperty(beanName);
            bean = Class.forName(beanPath).newInstance() ;
        } catch (Exception e) {
            e.printStackTrace();
        }

        return bean;
    }
}
```

要求对象是单例的

```java
package com.importsys.factory;

import java.io.InputStream;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

/**
 * 一个创建Bean对象的工厂
 * Bean在计算机英语中有可重用组件的含义
 * JavaBean：用java语言编写的可重用组件
 */
public class BeanFactory {
    private  static Properties props;

    private static Map<String, Object> beans;
    static {
        try {
            props = new Properties();
            //获取properties文件的流对象
            InputStream in = BeanFactory.class.getClassLoader().getResourceAsStream("bean.properties");
            props.load(in);
            beans = new HashMap<String, Object>();
            Enumeration keys = props.keys();
            while (keys.hasMoreElements()) {
                String key = keys.nextElement().toString();
                String beanPath = props.getProperty(key);
                Object value = Class.forName(beanPath).newInstance();
                beans.put(key, value);
            }
        }catch (Exception e) {
            throw new ExceptionInInitializerError("Initialize properties error");

        }
    }
    public static Object getBean(String beanName) {
        return beans.get(beanName);
    }
}
```
Client
```java
public class Client {
    public static void main(String[] args) {
        for (int i= 0; i < 3; i++) {
            IAccountService as = (IAccountService) BeanFactory.getBean("accountService");
            System.out.println(as);
            as.saveAccount();
        }
    }
}
```

IOC是什么：
控制反转（Inversion of Control，缩写为IoC），是面向对象编程中的一种设计原则，可以用来减低计算机代码之间的耦合度。其中最常见的方式叫做依赖注入（Dependency Injection，简称DI），还有一种方式叫“依赖查找”（Dependency Lookup）。通过控制反转，对象在被创建的时候，由一个调控系统内所有对象的外界实体，将其所依赖的对象的引用传递给它。也可以说，依赖被注入到对象中。