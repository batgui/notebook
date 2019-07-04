以太坊可编程的可支持各种各样的应用
以太坊是一个分布式状态机可以存储键值对key-value tuple 的数据

以太坊用把代码和数据存储在	memory中，用Ethereum blockchain来记录memory。
以太坊可以把代码载入状态机里面，运行，然后把结果放到blockchain里面
### 以太网组成部分
horror velvet child game park bike great forget friend knife page kiwi
P2P Network
以太坊在 以太坊主网 上运行，可以通过TCP端口30303访问，运行称作 ÐΞVp2p 的协议。

Consensus rules
以太坊的共识规则，在参考规范，即 [yellowpaper] 中定义。

Transactions
Ethereum交易（参见[transactions]）是网络消息，包括发送者，接收者，值和数据负载等。

State Machine
以太坊的状态转移由 Ethereum虚拟机（EVM） 处理，这是一个执行 bytecode（机器语言指令）的基于栈的虚拟机。称为“智能合约”的EVM程序以高级语言（如Solidity）编写，并编译为字节码以便在EVM上执行。

Blockchain
以太坊的区块链作为 database（通常是Google的LevelDB）存储在每个节点上，该区块链在称作 梅克尔帕特里夏树 Merkle Patricia Tree 的序列化哈希数据结构中包含交易和系统状态，。

Consensus Algorithm
以太坊目前使用名为_Ethash_的工作量证明算法，但有计划在不久的将来将过渡到称为_Casper_的权益证明（Proof-of-Stake）系统。

Clients
以太坊有几个可互操作的客户端软件实现，其中最突出的是 Go-Ethereum（Geth）_和_Parity。