spring事务传播属性和事务隔离级别

事务的传播行为
当事务方法被另一个事务调用时，必须制定事务应该如何传播。例如：方法可能继续在现有事务中运行，也可能开启一个新事务，并在自己的事务中运行。


REQUIRED
如果有事务在运行，当前的方法就找这个事务内运行，否则，就启动一个新的事务，并在自己的事务内运行
REQUIRED_NEW
当前的方法必须启动新事务，并在它自己的事务内运行，如果有事务正在运行，挂起这个事务。

事务在@Transactional 注解的propagation属性中定义。
@Transactional(propagation=Propagation.REQUIRED)

数据库并发问题

1. 脏读
当前transaction读取到了其他transaction还没有提交的值就是脏读。因为这时如果其他transaction回滚了，他们提交的值就是无效的。

比如说transaction #1在写入某个数据A后， transaction #2读取了A这个值，这个时候transaction #1回滚，A的值也回滚导致transaction #2读取的A是无效的。

2. 不可重复读
当前transaction在连续读取某个数据时，读取的值不一样、

transaction #1读取了某个数据A后，transaction #2将这个数据修改了，当transaction #1再次读取数据A时，读取的值和之前的不一样。

3. 幻读
	
transaction #1正在读取了表中的一部分数据时，transaction #2向这个表中插入了新的行，导致transaction #1在读取的时候多了几行。

为了解决上述问题，数据库引入了隔离级别的概念。

1. 读未提交(READ UNCOMMITTED)

允许transaction #1读取transaction #2未提交的修改

2. 读已提交(READ COMMITTED)

transaction #1只能读取transaction #2已经提交的修改

3. 可重复读(REPETABLE READ)

确保transaction在执行的时候可以多次从一个字段中读取相同的值，即 transaction在执行期间禁止其他事物对这个字段进行更新。

4. 串行化(SERIALIZABLE)

transaction在执行过程中是一个接一个执行的，没有并发操作。

{图片}

其中SERIALIZABLE不会存在脏读、不可重复读和幻读

REPETABLE READ可能会出现幻读

READ COMMITTED会出现不可重复读和幻读

READ UNCOMMITTED会出现脏读、不可重复读和幻读

{图片}

@Transactional(propagation=Propagation.REQUIRED, isolation=Isolation.READ_COMMITTED)

______________________________________



SpringMVC 如何解决POST请求乱码问题

@RequestMapping

public String test(Employee employee) {
	System.out.println("信息是："+ employee);
}

在web.xml上面配置过滤器
```xml
<filter>
	<filter-name>CharaterEncodingFilter</filter-name>
	<filter-class>org.springframework.web.filter.CharaterEncodingFilter</filter-class>
	<init-param>
		<param-name>encoding</param-name>
		<param-value>UTF-8</param-value>
	</init-param>
	<init-param>
		<param-name>forceEncoding</param-name>
		<param-value>true</param-value>
	</init-param>
</filter>
<filter-mapping>
	<filter-name>CharaterEncodingFilter</filter-name>
	<url-pattern>/*</url-pattern>
</filter-mapping>
```
然后重启服务器

对于GET请求，需要修改Tomcat的配置文件server.xml
在里面找到第一个Connector标签，加上URIEncoding="utf-8"
```xml
<Connector URIEncoding="utf-8" connectionTimeout="20000" port="8080" protocol="HTTP/1.1" redirectPort="8443"/>
```

____________________________________________

SpringMVC的工作流程

Spring处理模型数据有两种方式。
1. 将方法的返回值设置为ModelAndView
2. 在方法的入参里面传入Map、Model或者ModelMap

这两种方式SpringMVC最终都会转换为一个ModelAndView对象


——————————————————————————

MyBatis中当实体类中的属性名和表中的字段名不一样怎么办？

1. 写sql语句的时候起别名

在mybatis mapper文件里面写别名
select id, last_name lastName, email, salary, dept_id deptId from employees

2. 在 Mybatis的全局配置文件里面开启驼峰命名规则
<settings>
	<setting name="mapUnderscoreToCamelCase" value="true"/>
</settings>
这样的话可以将数据库中的下划线映射为驼峰命名。
3. 在Mapper映射文件中使用resultMap来自定义映射规则

```xml
<select id="getStudent" resultMap="getStudentRM">
  SELECT ID, Name, Age
    FROM TStudent
</select>
<resultMap id="getStudentRM" type="EStudnet">
  <id property="id" column="ID"/>
  <result property="studentName" column="Name"/>
  <result property="studentAge" column="Age"/>
</resultMap> 
```

_____________________________________

git 创建分支

git checkout -b <分支名>

合并分支
git checkout master
git merge <分支名>

删除分支

git checkout master
git branch -D <分支名>


git 推送

git add .
git commit -a -m "这次改了些啥？"
git push


git push免密码


ssh-keygen -t rsa -b 4096

把~/.ssh/id_rsa.pub拷贝到github设置中的SSH and GPG keys

git config --global user.email <email>
git config --global user.name <username>

________________________________

redis持久化方法

RDB(Redis Database)

在指定的时间间隔内将内存中的数据集快照写入磁盘，即snapshot，恢复是将快照文件直接读到内存里。

在备份的时候，Redis会fork一个子进程来进行持久化，先将数据写入临时文件，然后等持久化结束的时候，把临时文件写入磁盘。
优点是节省磁盘空间，恢复速度快。
如果Redis崩溃掉，会丢失最后一次快照的所有修改。
AOF(Append Of File)

以日志的方式记录每个写操作，只追加文件，Redis启动时会读取该文件重新构建数据。

优点，丢失数据概率低

缺点，占用磁盘空间多，恢复速度慢，性能较低。


——————————————————————————

Mysql 什么时候建立索引

索引是帮助Mysql高效获取数据的数据结构

优势：查询速度快，排序速度快

劣势：做写操作的时候速度会变慢，因为写操作的同时要更新索引。 

需要建索引的情况：
1. 主键自动建立唯一索引
2. 频繁作为查询条件的字段应该创建索引
3. 查询中与其他表关联的字段，外键关系建立索引
4. 单键/组合索引的选择问题，组合索引性价比更高
5. 查询中排序的字段，排序字段若通过索引去访问将大大提高排序速度
6. 查询中统计或者分组字段

不需要建立索引：
1. 经常增删改查的表或者字段
2. Where条件里用不到的字段
3. 过滤性不好的字段

——————————————————————————

JVM垃圾回收机制

垃圾回收机制发生在堆里面

GC分为三种：
次数上频繁收集的Young区 Minor GC
次数上较少收集的Old区 Full GC
几本不动的Perm区

GC收集的4个算法
1. 引用计数法
只要对象被引用了就不被回收
已经被淘汰因为无法处理循环引用。
2. 复制算法Young
从根集合开始，通过Tracing从From中找存活对象，拷贝到To中，然后From，To互换身份。
缺点，需要双倍空间
优点，没有标记和清除过程，效率高，没有内存碎片
3. 标记清除Old
标记幸存者，清除没有标记的
优点，不需要额外空间
缺点，两次扫描，会产生内存碎片

4. 标记压缩Old
先进行标记，再进行压缩
优点，没有内存碎片
缺点，需要移动对象

————————————————————————————————————————————————————

Redis在项目中使用场景

数据类型对应使用场景

String：什么时候封锁一个ip地址，用Incrby记录当前被访问的次数
Hash：用来存储用户信息[id, name, age] Hset(key, field, value)
List:实现最新消息的排行，可以利用List的push命令将任务存在List集合中。同时使用另一个命令将任务从集合中取出。我们用Redis List类型来模拟消息队列。比如说电商中的秒杀可以采用这种方式。
Set：特殊之处，可以自动排重。比如说微博将每个人的好友存在集合中。这样求两个人共同好友的操作，只需要求交集即可。
Zset：以某一个条件为权重进行排序。京东：商品详情，有综合排名，可以按照价格进行排名。


————————————————————————————————————————————————————————————


Elastic Search 和  solr 的区别

背景：它们都是基于lucene的搜索服务器基础上开发的高性能的搜索服务器。

因为它们都是基于分词技术构建的倒排索引进行查询的。

开发语言：基于Java语言开发

ES出现的更晚一些，功能更强大些。

1. 当实时建立索引的时候，solr会产生io阻塞，es不会，es的查询性能要高于solr。
2. 在不断动态的添加数据时，solr的检索效率会变得低下，而es没有什么变化。
3. Solr利用zookeeper进行分布式管理，es自身带有分布式管理功能。Solr一般需要部署到web服务器上才能使用，如Tomcat，启动Tomcat需要配置与Solr的关联。Solr本质是一个动态的web项目
4. Solr支持更多的格式数据[xml, json, csv], ES仅支持json格式。
5. Solr是传统应用搜索的有力解决方案，但是ES更适用于新兴的实时搜索应用。
 a)单纯的对已有数据进行搜索的时候solr效率更好。
6. Solr官网提供的功能更多， ES更注重于核心功能（搜索），更多功能需要插件。


————————————————————————————————————————————

单点登录实现过程

什么是单点登录：
一处登录多处使用。
单点登录多使用在分布式系统中

添加购物车
1. 用户未登录
	a. 添加到什么地方 
		redis？ ---京东 采用hash存储 hset(key, field, value) key: user:userId:cart Hset(key, skuId, value)
		cookie？ 如果
2. 用户登录状态
	redis 读写速度快
	存在数据库中
展示购物车
1. 未登录状态
	直接从cookie中取数据

2. 登录状态
	现实数据库 + cookie中购物车数据

________________________________________________

消息队列在项目中的使用

分布式系统中如何处理高并发
由于在高并发的环境下，来不及同步处理用户发送的请求，则会导致请求发生阻塞。 
数据库处理不了大量的请求，会触发too many errors的错误，使用消息队列可解决。

消息队列弊端

消息的不确定性，延迟队列和轮询技术解决问题。

推荐使用activeMQ




