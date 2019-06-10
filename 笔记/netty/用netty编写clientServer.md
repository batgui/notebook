@[TOC](如何用Netty进行socket编程)
# 如何用Netty进行socket编程

[前一篇文章](https://blog.csdn.net/qq_31027515/article/details/90613839)讲的是如何用Netty进行http服务器的编写，http是应用层协议，Netty不仅可以直接操作应用层，还可以接触最底层的socket服务，进行socket调用。

目前业界许多大数据开源项目都使用了Netty做底层传输的基础框架，如Spark等。而不是使用HTTP作为传输协议，因为http效率会很低，所以大部分都使用RPC。

用Netty进行socket编程和传统的java编程类似，我们需要编写客户端和服务器端。

本文主要介绍如何用Netty进行socket编程，以及如何用Netty编写Client Server程序。
## 工程结构
在src/main/java文件夹中建立如下工程。
![socketexample](https://img-blog.csdnimg.cn/20190530225139195.png)
然后在该工程下建立6个class文件，名称如下图所示。
![项目结构](https://img-blog.csdnimg.cn/20190530225018629.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMxMDI3NTE1,size_16,color_FFFFFF,t_70)
## Server部分编写

该部分用来编写和client通信的server端，该端接受client发送的请求，并回复client信息。

### Server主程序

Socket Server主程序的编写和Http Server类似（[点击查看](https://mp.csdn.net/mdeditor/90613839)）。

```java
public class TestServer {
    public static void main(String[] args) throws Exception {
        EventLoopGroup bossGroup = new NioEventLoopGroup();
        EventLoopGroup workerGroup = new NioEventLoopGroup();
        try {
            ServerBootstrap serverBootstrap = new ServerBootstrap();
            serverBootstrap.group(bossGroup, workerGroup).channel(NioServerSocketChannel.class).childHandler(new TestServerInitializer());
            ChannelFuture channelFuture = serverBootstrap.bind(8889).sync();
            channelFuture.channel().closeFuture().sync();
        } finally {
            bossGroup.shutdownGracefully();
            workerGroup.shutdownGracefully();
        }
    }
}
```

Server初始化过程用来添加几个过滤器，这些过滤器的功能包括，格式编解码，字符串编解码，以及我们自己的处理类。

### Server初始化
```java
public class TestServerInitializer extends ChannelInitializer<SocketChannel> {
    @Override
    protected void initChannel(SocketChannel ch) throws Exception {
        ChannelPipeline pipeline = ch.pipeline();
        pipeline.addLast(new LengthFieldBasedFrameDecoder(Integer.MAX_VALUE, 0, 4, 0, 4));
        pipeline.addLast(new LengthFieldPrepender(4));
        pipeline.addLast(new StringDecoder(CharsetUtil.UTF_8));
        pipeline.addLast(new StringEncoder(CharsetUtil.UTF_8));
        pipeline.addLast(new TestSocketServerHandler());
    }
}
```

其中LengthFieldBasedFrameDecoder是一个解码器。
LengthFieldPrepender是编码器会prepend消息的长度，把消息的长度作为二进制加如消息的头部。
StringDecoder 是字符串解码。

### Server请求处理
我们用ChannelHandlerContext类中的ChannelRead0函数收到数据，做处理，然后处理完成后把结果返回给客户端。

```java
public class TestSocketServerHandler extends SimpleChannelInboundHandler<String> {
    @Override
    protected void channelRead0(ChannelHandlerContext ctx, String msg) throws Exception {
        System.out.println(ctx.channel().remoteAddress() + ": " + msg);
        ctx.channel().writeAndFlush("message received.");
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) throws Exception {
        cause.printStackTrace();
        ctx.close();
    }
}
```
ChannelHandlerContext 表示上下文信息，比如说远程地址、channel对象。
msg是接收到的请求对象。


## Client部分编写
客户端只需要一个事件循环组就够了，并在在处理channel的时候使用handler函数，而不是childHandler。

若在服务器端的channel使用handler，则handler针对的是BossGroup的信息，使用childHandler 针对的是workerGroup里面的NIO信息（NIO线程）。

### Client主程序
```java
public class TestClient {
    public static void main(String[] args) throws Exception{
        EventLoopGroup eventLoopGroup = new NioEventLoopGroup();
        try {
            Bootstrap bootstrap = new Bootstrap();
            bootstrap.group(eventLoopGroup).channel(NioSocketChannel.class).handler(new TestClientInitializer());
            ChannelFuture channelFuture = bootstrap.connect("localhost", 8889).sync();
            channelFuture.channel().closeFuture().sync();
        } finally {
            eventLoopGroup.shutdownGracefully();
        }
    }
}

```

client端初始化和server较类似。
### Client初始化
```java
public class TestClientInitializer extends ChannelInitializer<SocketChannel> {
    @Override
    protected void initChannel(SocketChannel ch) throws Exception {
        ChannelPipeline pipeline = ch.pipeline();
        pipeline.addLast(new LengthFieldBasedFrameDecoder(Integer.MAX_VALUE, 0, 4, 0, 4));
        pipeline.addLast(new LengthFieldPrepender(4));
        pipeline.addLast(new StringDecoder(CharsetUtil.UTF_8));
        pipeline.addLast(new StringEncoder(CharsetUtil.UTF_8));
        pipeline.addLast(new TestClientHandler());
    }
}
```
client端消息处理和server也是异曲同工的。
### Client消息处理
```java
public class TestClientHandler extends SimpleChannelInboundHandler<String> {
    @Override
    protected void channelRead0(ChannelHandlerContext ctx, String msg) throws Exception {
        System.out.println(ctx.channel().remoteAddress() + ": " + msg);
        ctx.writeAndFlush("Hello Server");
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) throws Exception {
        cause.printStackTrace();
        ctx.close();
    }
}
```