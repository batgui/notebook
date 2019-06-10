---
title: CMU Advanced DB 课程笔记#1：Disk-oriented DBMS和In-memory DBMS对比
tags:
	- CMU Advanced DB course
categories:
	- 数据库
---
# Disk-oriented DBMS和In-memory DBMS对比

&nbsp; &nbsp; &nbsp; &nbsp; 数据库管理系统被创建之初，硬件设施是很简陋的，当时的CPU只有一核，RAM严重不足，数据库需要被存在硬盘中去，并且访问硬盘的速度极其的慢，当时数据库很大一部分都是在做将数据从硬盘和内存之间来回移动的工作。

&nbsp; &nbsp; &nbsp; &nbsp; 但是现在DRAM的存储空间越来越大，许多数据库都可以直接被放进内存中去（除了数据仓库等等），所以频繁访问硬盘所造成的低性能已经不能忽视了，In-memory DBMS开始兴起。

## Disk-oriented DBMS介绍

### 读数据操作
&nbsp; &nbsp; &nbsp; &nbsp; Disk-oriented DBMS:数据库的主要存贮地方是非易失性存储器（non-volatile storage）比如磁盘或者固态硬盘。当系统需要读取数据的时候，DB总是假定数据不在内存中，而在磁盘中，DB需要从磁盘中拿数据。
### 
&nbsp; &nbsp; &nbsp; &nbsp;数据库在磁盘中由固定大小的slotted pages组成，pages里面包含存入的数据（tuple）。当数据从磁盘中取出的时候，我们先把数据放在In-memory buffer pool中缓存起来。

&nbsp; &nbsp; &nbsp; &nbsp;In-memory buffer pool是数据库直接操作的对象，我们对buffer pool处理过后，数据才会被写到磁盘中。buffer pool manager负责数据在磁盘和内存之间的移动。

&nbsp; &nbsp; &nbsp; &nbsp;当query需要访问一个page时，DBMS先检查看看这个page是否已经在内存中，如果不在,DBMS就把数据从磁盘中取出来，拷贝到buffer pool中。如果buffer pool满了，DBMS需要回收pages。如果回收的pages是脏的，DBMS需要把这个page写到磁盘中。当page在内存中的时候，DMBS返回指向内存中pages的指针。
![data organization ](https://user-images.githubusercontent.com/20705797/58792522-ee83b900-8626-11e9-9dd8-03f4c82aa57a.png)

&nbsp; &nbsp; &nbsp; &nbsp;如上图所示，假设我们做一次数据库查询，我们搜索索引来找到一个特定的数据（tuple），我们遍历索引的B+树到叶子节点，得到一个指向page id和slot number的指针。然后我们根据page id查找page table。page table 里面存的数据如下：
```
page table： page id -> frame(in buffer pool)
```
&nbsp; &nbsp; &nbsp; &nbsp;假设page table里面没有我们需要的page id，并且page table满了，那么此时我们需要做两件事，一个是在page table中回收一个pages，然后从硬盘中把需要的数据拿到buffer pool中去，在做这个操作的时候我们需要对page table上锁，保证不出现竞争条件。同时对于回收的那条page 我们也需要上锁，保证在回收过程中没人操作它。	最后我们更新page table的数据，令page id指向新数据。

&nbsp; &nbsp; &nbsp; &nbsp;传统的Disk-oriented DBMS有很多缺点，比如说每次DB要访问数据的时候，一定要经过buffer pool manager把数据从硬盘拿到内存中去，这个过程很慢（需要加锁防止竞争）。并且每次访问数据的时候都要经过page table把page id转化为buffer pool里面的数据。

&nbsp; &nbsp; &nbsp; &nbsp;在传统的Disk-oriented DBMS,系统假定当一个transaction访问不在内存中的数据时会随时暂停。所以在这个过程中需要加锁来保证数据库的[ACID](https://en.wikipedia.org/wiki/ACID_(computer_science))特性。这些（放在内存中的）加锁信息被存储在另外的数据结构中，用来记录哪条transaction对哪条数据加什么类型的锁。

&nbsp; &nbsp; &nbsp; &nbsp;对于In-memory DBMS 数据库的锁和数据存储在一起，不需要去另外的数据结构中查看加锁信息。

### 日志和恢复机制：STEAL + NO-FORCE policy.
&nbsp; &nbsp; &nbsp; &nbsp;STEAL的意思是被没有commit的transaction修改的page可以被写入硬盘，反之NO-STEAL就是不被允许写入硬盘。FORCE的意思是当transaction被commited后，buffer pool里面的所有dirty pages都要被flush到硬盘中，反之NO-FORCE就是不用flush到硬盘中。数据库通过写前日志（WAL）来实现这个机制。
&nbsp; &nbsp; &nbsp; &nbsp;下图是各个policy之间效率的对比图，可以看出STEAL + NO-FORCE policy速度最快，但是database从崩溃到恢复所需要的时间也最长。

![bufferpool policy](https://user-images.githubusercontent.com/20705797/58792521-edeb2280-8626-11e9-91d3-8d6ec115e0b6.png)

&nbsp; &nbsp; &nbsp; &nbsp;可以从下图看到，Disk oriented DB真正有用的工作只占CPU 7%的工作时间，大部分时间都花在buffer pool还有加锁的过程中。

![measureCPU](https://user-images.githubusercontent.com/20705797/58792525-efb4e600-8626-11e9-91ae-ee3c8557115e.png)
这就引出了In-memory DBMS。In-memory DBMS假定数据存储在内存中的。

## In-memory DBMS介绍

### 数据组织形式
&nbsp; &nbsp; &nbsp; &nbsp;In-memory DBMS 将数据以block的形式组织起来，并把定长的数据和不定长的数据分开存储。
![inmem data organization](https://user-images.githubusercontent.com/20705797/58792524-ef1c4f80-8626-11e9-917d-133fb2aa8547.png)
&nbsp; &nbsp; &nbsp; &nbsp;如上图所示当我们想要访问一条数据时，我们从遍历index得到数据的block id和offset，我们可以用id和offset直接找到我们想到的数据。

&nbsp; &nbsp; &nbsp; &nbsp;In-memory database 把锁和数据存在一起，可以更快的判断数据有没有上锁。而disk-oriented databse把锁和数据分开来存。

### 索引

&nbsp; &nbsp; &nbsp; &nbsp;B+树在In-memory DB中仍然是建立索引比较不错的数据结构。与disk oriented DB不同的是，In-memory database不会将更新索引的log写入到磁盘中，而是在计算机重启后从硬盘中载入整个数据库的时候重新建立索引，而disk oriented DB在更新数据的时候会将更新索引的log写入到磁盘中，来减少数据库恢复所需要的时间。
### 查询
&nbsp; &nbsp; &nbsp; &nbsp;和disk oriented DB不同，顺序扫描比随机扫描快不了多少，并且tuple-at-a-time iterator model不适用，因为函数调用overhead太多会导致速度很慢。

### 日志和恢复
&nbsp; &nbsp; &nbsp; &nbsp;In-memory DB也需要写前日志（WAL），但需要记录的东西少很多，比如说不需要记录redo操作和LSN。为了加快恢复速度，In-memory DB也需要不定时的对数据库进行checkpoint操作。