# Maven教程

Maven是一款基于JAVA平台的自动化构建工具。本节介绍Maven的安装和基础知识。

###Maven 安装
####安装JAVA并设置JAVA_HOME变量
在安装Maven之前首先要确保JAVA已经安装到系统中，并正确设置了JAVA_HOME变量。
在linux环境下，输入

```
echo $JAVA_HOME
```
若返回值为path_to_jdk，则说明JAVA设置正确。
####解压Maven核心程序包，并将解压路径添加到PATH环境变量中去。
```
tar -xvzf apache-maven-3.6.1-bin.tar.gz
```
然后在命令行中输入
```
mvn -v
```
如果输出结果不为空，则表明Maven安装成功。
####创建一个Maven工程
运行如下代码创建一个Maven工程，其中groupdId是公司或者组织域名+项目名，artifactId是模块名。
```
mvn -B archetype:generate -DarchetypeGroupId=org.apache.maven.archetypes -DgroupId=com.first.app -DartifactId=first-maven-app
```

在创建成功之后，我们打开这个工程，可以看到一个名为pom.xml的文件，
POM.xml是项目对象模型，是Maven的核心配置文件，与构建过程中的一切设置都在这个文件中配置。该文件的内容如下图所示。

```
xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/maven-v4_0_0.xsd">
  <modelVersion>4.0.0</modelVersion>
  <groupId>com.first.app</groupId>
  <artifactId>first-maven-app</artifactId>
  <packaging>jar</packaging>
  <version>1.0-SNAPSHOT</version>
  <name>first-maven-app</name>
  <url>http://maven.apache.org</url>
  <dependencies>
    <dependency>
      <groupId>junit</groupId>
      <artifactId>junit</artifactId>
      <version>3.8.1</version>
      <scope>test</scope>
    </dependency>
  </dependencies>
</project>
```

其中packaging是打包格式，version是工程版本，name是工程的名字。 
####输入测试代码
在**src/main/java/com/first/app/App.java**中输入如下代码
```
package com.first.app;

public class HelloWorld {
public static void main(String[] args) {
  HelloWorld myWorld = new HelloWorld();
  String said = myWorld.sayHelloTo("World");
  System.out.println(said);
 }
 public String sayHelloTo(String to) {
  return "Hello "+to+"!";
 }
}
```
然后我们就可以用
```
mvn compile
```
命令编译主程序了。