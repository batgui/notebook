并发控制

数据库的并发控制允许多条transactions在数据库中同时运行，多条transactions在数据库中的运行结果和单条transaction一个接一个运行的结果相同，给外界一种每条transaction都单独在数据库中运行的错觉。

要进行并发控制需要维护每个transaction的信息包括如下几点
状态：当前transaction的执行状态
Undo Log：储存在内存里的数据结构中，当commit时丢弃
Redo Log:写到内存里的WAL(write ahead log)尾部，当commit的时候写到硬盘中
Read/Write集合：transaction读取和写入的数据集合。

目前主要有两种并发控制策略。
1 Two-Phase Locking（2PL）：2PL假设transactions会互相之间起冲突，所以transaction在访问数据的时候需要先对数据库数据上锁。
2 Timestamp Ordering（T/O）：T/O假定冲突很少，所以在访问数据的时候不对数据上锁，而是在commit的时候检查transaction之间是否起了冲突。

Two-Phase Locking分为两个阶段，如下图所示。
{图片}
1 Two-Phase Locking
Growing Phase和Shrinking Phase。
transaction在访问数据之前会对数据上锁，这个阶段是Growing Phase，一旦transaction释放了第一个锁，那么就进入了Shrinking Phase。在Shrinking Phase的时候，transaction只能释放锁或者对已经加锁了的数据进行操作，transaction不能获取新的锁。

如下图所示假设Txn #1和Txn #2同时运行，Txn #1先获取了对A的锁，Txn #2获取了对B的锁，紧接着Txn #1要获取对B的锁，这个时候Txn #1会暂停等待Txn #2释放对B的锁，假设此时Txn #2又想获取对A的锁，此时两个transaction都会暂停，进入死锁（dead lock）的状态。
{图片}

有两种防止死锁的方法
1. Deadlock Detection：每个transaction都维护一个队列，里面存放着该transaction需要等待锁。另外的一个线程查看这些队列来寻找死锁，如果找到了死锁就用某种方法kill掉一个transaction来打破死锁状态。
2. Deadlock Prevention：在加锁的时候查看是否有其他Txn已经拥有这个锁了。当拿不到锁的时候Txn有三种选择1 等待 2 自杀 3 kill拥有锁的Txn。

2 Timestamp Ordering
Timestamp Ordering主要有两种协议
Basic T/O
