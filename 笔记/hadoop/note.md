大数据生态体系

数据库（结构化数据）：Sqoop数据传输，如导入到HIVE中
文件日志（半结构化数据）：Flume日志收集
视频，音频（非结构化数据）：Kafka消息队列

我们用yarn来进行资源管理，用MapReduce进行离线计算，用spark Core进行内存计算。

在MapReduce中，用Hive进行数据查询，用Mahout进行数据挖掘。
在spark Core中，用Spark Mlib进行数据挖掘，Spark R进行数据分析，Spark sql进行数据查询，Spark streaming 进行实时计算（准实时）。
我们也可以用Storm进行实时计算。
