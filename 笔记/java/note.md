Java 中的集合分为value，keyvalue两种

存储值得有List和Set
List是有序的，可以重复的
Set是无序的，不可重复的，根据
equals和hashcode判断，如果一个对象要存储在set中，必须重写equals和hashCode方法。


List分为ArrayList和LinkedList
区别
ArrayList底层使用数组，LInked
使用链表。

HashMap和HashTable都可以使用存储Key-Value。
HashMap是可以把null作为key或者value
HashTable不可以
Hashmap是线程不安全的，效率高
HashTable是线程安全的，效率低。

如果我想线程安全又想效率高
ConcurrentHashMap

把大Map分成n个segment，可以提供相同的线程安全，但是效率提升n倍。


Servlet，是用Java编写的服务器端程序，Servlet是指任何实现了这个Servlet借口的类
功能主要在于交互式的浏览和修改数据，生成动态Web的内容，Servlet运行于支持Java的应用服务器中
HttpServlet重写doGet和doPost方法完成对get和post请求的响应

servlet的生命周期

加载Servlet的class--->实例化servlet---->调用servlet的init完成初始化----->响应请求（servlet的service方法）---->Servlet容器关闭（Servlet的destroy方法）

Servlet API中forward和redirect区别
前者仅是容器中控制权的转向，在客户端浏览器地址栏中不会显示出转向后的地址，后者是完全的跳转，浏览器将会得到跳转后的地址，并重新发送请求连接，因此在地址栏可以看到跳转后的连接地址。
forward还是原来的请求，redirect是重新发起请求

forward是服务器端的转向，redirect是客户端的跳转。

JSP和Servlet相同点和不同点：
JSP是Servlet技术的扩展，所有jsp文件都会被翻译为一个继承HttpServlet的类，也就是jsp最终也是一个Servlet.这个Servlet对外提供服务。
不同点：
Servlet的应用逻辑是在Java中，并且完全从表示层的HTML里分离开来。Servlet如果要实现html的功能，必须使用Writer输出对应的Html。而JSP的情况是Java和HTML可以组合成一个扩展名为.jsp的文件，JSP侧重于视图，而Servlet主要用于控制逻辑。

Session和Cookie的区别

Session和Cookie都是会话跟踪技术。Cookie通过在客户端记录信息确定用户身份，Session通过在服务器端记录信息缺点用户身份。但是Session的实现依赖于Cookie，sessionId（session的唯一标识需要存放在客户端）。
cookie不是很安全，别人可以分析存在本地的Cookie并进行Cookie欺骗，考虑到安全应当适当使用session。
session会在一定时间保存在服务器上，当访问增多，比较占用服务器性能，考虑减轻服务器性能方面，应该使用Cookie。
单个cookie保存的数据不能超过4k。
将登陆信息等重要信息保存在Session中
其他信息如果需要保留可以放在Cookie中

因为cookie是可以在客户端禁用的，这时候我们需要使用cookie + 数据库的方式实现，当从cookie中不能获取数据时，就从数据库获取。

MVC：
Model javabean
View html jsp
Control Servlet 

线程池的作用

限定线程的个数，不会导致由于线程过多导致系统运行缓慢或者崩溃。
线程池不需要每次都去创建或者销毁，节约了资源
线程池不需要每次都去创建，响应更快。


数据库的分类。

关系型数据库和非关系型数据库。

关系型数据库的三范式。

要想满足第二范式，必须先满足第一范式。
第一范式：数据库表中的每一列都是不可分割的基本数据项，同一列中不能有多个值，即实体中的某个属性不能有多个值或不能有重复的属性。列数据的不可分割。
第二范式：要求数据库表中的每个实例或行必须可以被唯一的区分，为实现区分，通常需要为表加上一个列，以存储各个实例的唯一标识。（主键）
第三范式：要求数据库表中不包含已经在其他表中已包含的非主键关键字。（外键）
反三范式：有的时候为了效率查询，可以设置重复的字段。

mysql数据库的最大连接数
特额定服务器上面的数据库只能支持一年数据同时连接，这时需要我们设置最大连接数，在数据库安装时都会有一个默认的最大连接数。

默认为100。

mysql的分页和oracle的分页
为什么需要分页，在很多数据时，不可能完全显示数据，进行分段显示。

Mysql是使用关键字limit进行分页的， limit offset，size表示从多少索引去多少位。

Oracle的分页，大部分情况下，我们是记不住的。要使用三层嵌套查询，

触发器需要有触发条件，当条件满足以后，做什么操作。


有没有使用过redis
redis 是一个key value 的数据库，先存到内存中，会根据一定的持久化策略写到磁盘，即使断电也不会丢失数据。

可以用来缓存数据库的数据，和web集群时当做中央缓存存放session。

把经常需要查询，很少需要修改的数据，放在内存中，以便下次访问减少时间。

redis中的计数器是原子性的内存操作。
可以解决库存溢出的问题
web集群时，作为session缓存服务器
缓存队列

对象保存方式

1 json：需要手动把对象转换为json字符串，当做字符串处理，直接使用set和get来设置和获取。
2 字节流：


redis的数据淘汰机制

在redis中，允许用户设置最大使用内存大小server.maxmemory,在内存限定的情况下是很有用的。
在redis中，内存数据大小上升到一定大小的时候，会实行数据淘汰机制

volatile-lru 从已设置过期	时间的数据集server.db[i].expires中挑选最少使用的来淘汰
volatile-ttl 从已设置过期	时间的数据集server.db[i].expires中挑选要过期的数据进行淘汰

volatile-random 从已设置过期	时间的数据集server.db[i].expires中随机淘汰

allkeys-lru 从数据集（server.db[i].dict）中挑选最近最少使用的数据淘汰

allkeys-random 从数据集（server.db[i].dict）中随机淘汰

no-enviction:禁止淘汰数据