---
title: CMU Advanced DB 课程笔记#2：数据库工作负载和数据库事务模型
tags:
	- CMU Advanced DB course
categories:
	- 数据库
	- 事务模型
---

# CMU Advanced DB 课程笔记#2：数据库工作负载和数据库事务模型

## 数据库工作负载：
数据库工作负载有主要分为两种：
&nbsp; &nbsp; &nbsp; &nbsp;在线事务处理（OLTP）:每次只读取或更新数据库的一小部分，比如说用户去淘宝购物，用户只能对自己的购物车或者地址进行操作，这些操作只会涉及到很小的一部分数据。

&nbsp; &nbsp; &nbsp; &nbsp;在线分析处理（OLAP）:和OLTP不同的是，OLAP会对数据库的大量数据进行操作，例如进行连接或聚合运算，比如说淘宝会对大量的用户数据进行分析，来帮助淘宝进行商业决策，更好的为用户服务。

&nbsp; &nbsp; &nbsp; &nbsp;近几年出现了混合事务+分析处理（HATP）的数据库，在HATP数据库中既可以进行OLTP操作，又可以进行OLAP操作，避免了资源的浪费。

&nbsp; &nbsp; &nbsp; &nbsp;如下图所示是常见的企业配置数据库的方式，公司用前端的OLTP数据库来进行事务处理，一个公司可以有好几个OLTP数据库。当公司想要对这几个OLTP数据库内的数据进行分析的时候，公司需要把数据从OLTP数据库拿出来，进行提取转换加载（ETL）操作，该操作会对数据进行清洗以及转换，把数据格式统一起来加载到后端的OLAP数据库中。然后在OLAP数据库中进行分析操作，必要的时候OLAP数据库还会给OLTP数据库返回计算的结果。
![bifurcated env](https://user-images.githubusercontent.com/20705797/59030421-84238080-8893-11e9-9851-d54acd972f1d.png)
&nbsp; &nbsp; &nbsp; &nbsp;以淘宝为例，淘宝在前端用OLTP收集用户的物品点击信息，在后端OLAP数据库中计算用户可能感兴趣的物品，将这个物品返回给前端OLTP数据库，以便用户下次访问的时候将这个物品呈现给用户。

&nbsp; &nbsp; &nbsp; &nbsp;HTAP数据库允许了某些只能运行在后端OLAP数据库的操作运行在前端OLTP数据库中，减少了数据从
```
OLTP DB --> ETL --> OLAP DB --> OLTP DB
```
 之间传输的时间，但是HTAP不能取代ETL。

### 数据库事务（Transaction简称为Txn）：

&nbsp; &nbsp; &nbsp; &nbsp;Transaction是数据库管理系统执行过程中的一个逻辑单位，由一个有限的数据库操作序列构成。---维基百科

## Transaction Model：
### Flat Txns:

&nbsp; &nbsp; &nbsp; &nbsp;我们现在所说的transaction大多指的是Flat Txns。Flat Txns以**BEGIN**开头，后面跟着一系列操作，最后以**COMMIT**或者**ROLLBACK**结束。

&nbsp; &nbsp; &nbsp; &nbsp;如下图所示，**Txn #1**以**BEGIN**开头，紧接着对A进行读取，对B进行写操作，最后**COMMIT**，表明B被永久写入数据库中了， **Txn #2**在对B进行写操作之后**ROLLBACK**，表明对B的写操作会回滚，B不会被写入数据库中。

![FLat ](https://user-images.githubusercontent.com/20705797/59030422-84238080-8893-11e9-92ce-76db5de1ae6e.png)

&nbsp; &nbsp; &nbsp; &nbsp;Flat Txns的缺点：当数据库需要**rollback**的时候，需要**rollback**这个transaction的所有操作。当数据库在进行transaction的时候崩溃了，所有对数据库的写操作都会丢失。比如说银行需要对大量用户数据进行更新，使用FLAT Txns会花费大量的时间更新数据，若这时数据库崩溃或冲突所有操作都会丢失。


### Flat Txns+ Savepoints：

&nbsp; &nbsp; &nbsp; &nbsp;为了解决Flat Txns的这个缺点，我们可以给DB加savepoint，savepoint保存了transaction当前的状态，允许用户访问这个状态。用户可以用**ROLLBACK**命令回滚到某个savepoint，用RELEASE来摧毁某个savepoint。
&nbsp; &nbsp; &nbsp; &nbsp;如下图所示，**Txn #1**在**BEGIN**语句执行时候自动生成一个new savepoint，然后对这个savepoint写入A。


![savepointA](https://user-images.githubusercontent.com/20705797/59030418-838aea00-8893-11e9-8579-839969c9e0d4.png)

&nbsp; &nbsp; &nbsp; &nbsp;在执行命令savepoint 1的时候将new savepoint重命名为savepoint 1。然后生成一个新的savepoint：new savepoint用来保存之后的操作。

![savepoint1](https://user-images.githubusercontent.com/20705797/59030417-838aea00-8893-11e9-877b-15fb6c573b4c.png)

&nbsp; &nbsp; &nbsp; &nbsp;在运行WRITE(B)的时候将B写入new savepoint中。当执行ROLLBACK To 1的时候，会把刚刚创建的savepoint删掉，重新建立一个new savepoint用来保存之后需要写入的C。所以当最后**COMMIT**的时候A和C会写入数据库中，B不会。

![savepoint](https://user-images.githubusercontent.com/20705797/59030416-82f25380-8893-11e9-8632-9d375bae4281.png)

### Nested Txns
&nbsp; &nbsp; &nbsp; &nbsp;Nested Txns是在进行transaction的时候调用了其他transaction，子transaction的结果取决于父transaction。我们用下面这个例子看一下。

![nest txn](https://user-images.githubusercontent.com/20705797/59030425-84bc1700-8893-11e9-9097-9f707cbe257d.png)

&nbsp; &nbsp; &nbsp; &nbsp;如上图所示，**Txn #1**在执行的时候调用了**Sub-Txn #1.1**,然后**Sub-Txn #1.1**又调用了**Sub-Txn #1.1.1**。因为在**Sub-Txn #1.1**最末尾进行了**ROLLBACK**，所以**Sub-Txn #1.1.1**和**Sub-Txn #1.1**的所有操作都无效。因此当**Txn #1** **COMMIT**的时候只有A被写入数据库中。

![nest txn2](https://user-images.githubusercontent.com/20705797/59030427-8554ad80-8893-11e9-831c-4ab69f032a11.png)


### Chained Txns：

&nbsp; &nbsp; &nbsp; &nbsp;Chained Txns是一个接一个的连续执行多个transactions，这些transactions之间的**COMMIT**和**BEGIN**操作是原子性的（atomic）。 与savepoint不同的是，在一个transaction **COMMIT**之后数据库可以释放这个transaction的锁，并且transaction **COMMIT**后不能**ROLLBACK**。

&nbsp; &nbsp; &nbsp; &nbsp;如下图所示，**Txn #1**在执行**COMMIT**命令后将A写入数据库中，**Txn #2**在执行**COMMIT**命令后将B写入数据库中，**Txn #3**在进行WRITE( C)操作后，即使进行了**ROLLBACK**也只对C有效，A和B不受影响。

![txn chain](https://user-images.githubusercontent.com/20705797/59030419-84238080-8893-11e9-9c14-552afec771e1.png)

&nbsp; &nbsp; &nbsp; &nbsp;若想逆转已经**COMMIT**的transaction的结果，我们需要Compensating Txn。
### Compensating Txns：
&nbsp; &nbsp; &nbsp; &nbsp;Compensating Txn具有以逆转已经**COMMIT**的transaction的功能。把Chained Txns和Compensating Txn加在一起，就是Saga Txns。
### Saga Txns：

&nbsp; &nbsp; &nbsp; &nbsp;Saga Txns由一系列Chained Txns T1-Tn和Compensating Txns C1-Cn−1组成。这些transaction将会以 T1,. . .Tj,Cj. . .C1  (其中j < n)的顺序进行**COMMIT**。Saga Txns允许数据库支持长时间运行的，多步的transaction。

&nbsp; &nbsp; &nbsp; &nbsp;如下图所示，假设**Txn #1**，**Txn #2**，**Txn #3**是Chained Txns，在运行**Txn #3**的时候程序中断，若此时什么都不处理则**Txn #1**和**#2**的的产物A + 1和B + 1仍然会被写入数据库中。

![saga txns1](https://user-images.githubusercontent.com/20705797/59030414-82f25380-8893-11e9-8f99-13bd97a88bd3.png)

&nbsp; &nbsp; &nbsp; &nbsp;Saga Txns会继续运行Compensating Txns，从后往前逆转已经**COMMIT**的transactions的操作。

![saga txn2](https://user-images.githubusercontent.com/20705797/59030412-8259bd00-8893-11e9-83f3-97a137511693.png)

&nbsp; &nbsp; &nbsp; &nbsp;目前没有数据库内在支持Chained Txns和Saga Txns，支持他们的大多是编程框架，特别是微服务（micro services）。因为微服务每次通常只会更新很小的数据，通过使用Saga Txns我们可以安全的对大量的微服务进行更新。