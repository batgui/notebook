protobuf vs thrift

websocket 连接与连接之间有状态保存，向服务器发送http请求要求服务升级，如果服务器支持的话，则建立websocket连接,搭配heartbeat模式，确保连接保持。


gradle ： maven都是xml形式  配置十分冗长 
gradle 使用groovy语言，使用编程的方法定义任务，定义构建步骤，比xml更加灵活和方便。是google开发android 官方工具


maven central


netty 
1 ：作为RPC框架，实现远程过程的调用 
2 ：作为长连接的服务器  websocket
3： 作为http 服务器 类似tomcat 采取的编程模型和获取请求模型不遵循serlvet规范，有自己一套处理方式。


channel  相当于 连接

channel handle 过滤器

pipeline  管道 又多个channel handle 共同构成

netty大多对线程的处理，对io的调度（异步）

bossGroup 接受连接，但不处理给workerGroup处理
workerGroup 获取参数 进行业务处理返回客户端

ServerBootstrap是简化服务端启动的class

ChannelInitializer 里面的initChannel 连接被注册时候ChannelInitializer被创建然后立即调用initChannel方法

HttpServerCodec对web请求进行编解码操作

Ctrl + i 调出继承类未实现的方法


channelread0读取客户端发送的请求，并向客户端返回响应的代码

FullHttpResponse类构建响应，接受的参数：协议类型，返回状态，返回内容。


ctx.writeAndFlush把内容返回给客户端。



**************************************************


在浏览器中输入一个网址时会发送两个请求，第一个是输入的网址，第二个是网址的图标favicon.ico


SimpleChannelInboundHandler对进来的请求的响应的处理


SimpleChannelInboundHandler继承ChannelInboundHandlerAdapter，有很多与事件相关的方法：channelRegistered channelUnregistered  这些是事件回调方法，在某个事件发生的时候会被netty引擎回调


handler added
channel registered
channel active
request function name: GET
channel inactive
channel unregistered

handler added
channel registered
channel active
request function name: GET
channel inactive
channel unregistered
request function name: GET
request favicon.ico
浏览器访问完没有channel inactive，channel unregistered出现，而用curl就出现呢

curl是完整的网络命令工具，请求完之后 请求就关闭掉了，服务器就接受通知，浏览器不一样

http 是请求和响应模式无状态协议，http底层是基于socket，netty最底层是server socket，对于上层应用，当获取客户端请求，判断是否基于http1.1协议，http1.1有keep alive时间，在规定时间内客户端没有再发送请求，服务器会主动把连接关掉，若基于http1.0的协议，请求发过来之后，服务器就把连接关闭掉。

如果是spring MVC，在处理完请求返回给用户之后，Tomcat会保证响应的连接会自动关闭掉。如果是netty需要自己做，需要自己写代码令服务器端主动关闭掉。


channel本身可以看做连接，我们可以把这个连接关闭掉，返回一个异步的ChannelFuture，判断响应的关闭状态。
channel inactive
channel unregistered

请求的类
DefaultHttpRequest

LastHttpContent$1


————————————————————————————————————————————————————————————————————


Netty socket

用netty 编写服务器处理请求，响应和spring MVC差不多，只不过netty没有实现serlvet规范。

规范定义请求是什么样子，如何获取请求参数（request.getparameters）

spring MVC 底层是serlvet，作了封装 参数绑定， 绑定对应请求方法的参数上面。

netty不是这样，我们需要忘掉spring， 有自己的一种方式，如果使用netty使用http 效率和吞吐量一定要比其他高。 适用于高并发场景。

框架将底层的基础设施构建好了，把响应代码填进去，比如说将control填进去

netty对请求  路由没有任何支持，比如说在control某个方法定义一个url request mapping， 填写url，固定url，带参数url,spring MVC有这个功能

匹配了对应的url，请求就会进入特定的方法里面。netty对这个没有任何支持，请求路由需要我们自己写，github有第三方项目  注解，配置文件等方式对请求路由进行映射。


netty socket开发  是RPC的一种方式
http是应用层的协议, netty可以接触最底层的socket信息,进行socket调用。

业界许多netty开源项目，在一定程度上用netty做底层传输的基础框架，在传输机制之上用户可以定义协议和规范。

进行微服务的开发，用http效率大打折扣，所以用RPC，如spark底层用netty做数据传输。

netty可以支持长连接的开发

要想使用长连接 如在线推送 在线聊天，需要实时保证，用websocket，websocket是html5规范组成部分，实现客户端和服务器的持续连接，客户端可以向服务器端发送	请求，服务器端也可以向客户端推送数据。 否则就要使用轮询，效率极低。并且用http需要发送一堆头信息，没有必要。websocket可以仅仅传递数据本身，不需要传递头数剧，效率极高。


用netty socket 可以自定义协议，定义请求头，请求长度，请求内容本身，定义结束符号，分隔符。netty进行编解码，然后可以发送给对方。

netty socket编程模式和http编程类似。


socket编程的客户端需要自己写，和传统的java编程类似，我们需要编写客户端和服务器端。

LengthFieldBasedFrameDecoder是一个解码器。
LengthFieldPrepender是编码器会prepend消息的长度，把消息的长度作为二进制加如消息的头部。
StringDecoder 字符串解码。


ChannelHandlerContext 表示上下文信息 比如说远程地址，比如说channel对象， msg是接收到的请求对象


ChannelRead0 收到数据，做一些处理，然后处理完成后把结果返回给对方。


客户端只需要一个事件循环组就够了

childHandler 和handler区别

handler 针对BossGroup的信息。
BossGroup 是
childHandler 处理workerGroup里面的NIO线程发挥作用。