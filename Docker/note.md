Docker需要隔离的内容如下

UTS 主机名和域名

Mount 文件系统

IPC 信号量，消息队列，共享内存

PID 进程编号

USER 用户和用户组

Network 网络设备，网络栈，端口

每一种资源在内核中只要可以切分为几个相互隔离的运行环境，我们就称之为namespaces

我可以在同一个内核之上创建多个名称空间的

clone().setns() : 克隆一个进程并放到namespace里面

整个linux领域所有容器技术都是靠内核级的6个namespace和chroot来实现的

