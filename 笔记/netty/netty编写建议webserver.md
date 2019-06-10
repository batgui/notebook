
## Netty：简易Http Webserver编写

### Netty 介绍
Netty 是一个基于NIO的客户、服务器端编程框架。使用Netty可以使我们快速简单的开发网络应用。

Netty有很多功能，我们可以用Netty作为RPC框架，实现远程过程的调用；也可以编写长连接的服务器，使用websocket等功能；我们还可以把Netty当做http服务器（类似Tomcat），对http请求进行接收和响应。用Netty编写服务器时，采取的编程模型和获取请求模型不遵循serlvet规范，Netty有自己一套处理方式。

下面我们进行一段简易HttpServer的编写（作者使用Intellij IDEA进行Netty项目的开发）。

### 创建Netty工程

打开IDEA，创建一个gradle项目。

![Netty工程创建](https://img-blog.csdnimg.cn/20190528091622233.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMxMDI3NTE1,size_16,color_FFFFFF,t_70)
点击下一步，输入GroupID（公司域名反转）和ArtifactID（模块名）

![设置groupId，ArtificatId](https://img-blog.csdnimg.cn/20190528091656807.png)
然后一直点下一步直到FInished。

至此我们便创建了一个工程，工程目录如下图所示：

![工程目录](https://img-blog.csdnimg.cn/20190528091739177.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMxMDI3NTE1,size_16,color_FFFFFF,t_70)
我们在src/main/java文件夹中编写应用代码,src/test中是我们编写测试文件用的，本文忽略测试文件。

### 导入netty jar包

导入netty jar包的过程很简单，我们可以在build.gradle文件的dependencies下加入下面一行代码：
```
compile group: 'io.netty', name: 'netty-all', version: '4.1.36.Final'
```
如下图所示
![导入depencencies](https://img-blog.csdnimg.cn/20190528091811346.png)
最新引入netty的代码可以在[maven repository](https://mvnrepository.com/artifact/io.netty/netty-all)中通过搜索netty all关键词找到。

然后我们就可以进行HttpServer的编写了。

### Server编写
右击src/main/java文件夹，new一个新的package，如下图所示。

![new package](https://img-blog.csdnimg.cn/2019052809183726.png)
然后在这个package中创建一个class名为**TestServer**
![new TestServer](https://img-blog.csdnimg.cn/20190528091859634.png)

在TestServer class中创建**main**函数,在**main**函数里面我们创建两个**NioEventLoopGroup**,分别为bossGroup，workerGroup。
```java
        EventLoopGroup bossGroup = new NioEventLoopGroup();
        EventLoopGroup workerGroup = new NioEventLoopGroup();
```
bossGroup接受连接请求并把请求交给workerGroup处理;workerGroup获取请求参数,进行业务处理，然后把结果返回客户端。

然后创建**ServerBootstrap** 类的实例，**ServerBootstrap** 是简化服务端启动的类。该类通过反射的形式创建NioServerSocketChannel。

channel相当于链接，同用户端进行网络连接、关闭和读写。

最后调用**ChildHandler**方法，里面传入一个对请求进行处理的类，在本例代码中我们传入我们编写的**TestServerInitializer**实例（请看下一节）。

```java
ServerBootstrap serverBootstrap = new ServerBootstrap();
            serverBootstrap.group(bossGroup,workerGroup).channel(NioServerSocketChannel.class)
                    .childHandler(new TestServerInitializer());
```

然后我们把这个服务器绑定在8888端口上，就可以接受用户端的请求了。

```java
            ChannelFuture channelFuture = serverBootstrap.bind(8888).sync();
            channelFuture.channel().closeFuture().sync();
```

完整代码如下图所示：

```java
public class TestServer {
    public static void main(String[] args) throws Exception {
        EventLoopGroup bossGroup = new NioEventLoopGroup();
        EventLoopGroup workerGroup = new NioEventLoopGroup();
        try {

            ServerBootstrap serverBootstrap = new ServerBootstrap();
            serverBootstrap.group(bossGroup,workerGroup).channel(NioServerSocketChannel.class)
                    .childHandler(new TestServerInitializer());
            ChannelFuture channelFuture = serverBootstrap.bind(8888).sync();
            channelFuture.channel().closeFuture().sync();

        } finally {
            bossGroup.shutdownGracefully();
            workerGroup.shutdownGracefully();

        }

    }
```
### ServerInitializer编写
![New serverInitializer](https://img-blog.csdnimg.cn/20190528091925263.png)
在同一个package中创建**TestServerInitializer**类，该类需要继承**ChannelInitializer**类，同时需要实现**initChannel**方法。

在连接被注册的时候，即**ChannelInitializer**被创建时会立即调用**initChannel**方法。

我们在该方法中创建一个pipeline。**ChannelHandler** 类似过滤器；**ChannelPipeline** 是管道，由多个channel handle共同构成。**ChannelHandler** 和**ChannelPipeline** 用于channel事件的拦截和处理。

在这个管道中我们先加入**HttpServerCodec**。**HttpServerCodec** 是一个用于对web请求进行编解码操作的Channelhandler。然后我们再加入**TestHttpServerHandler**（请看下一节），这个handler是一个我们自己编写用于对请求进行操作的类。

具体代码如下图所示。

```java
public class TestServerInitializer extends ChannelInitializer<SocketChannel> {
    @Override
    protected void initChannel(SocketChannel ch) throws Exception {
        ChannelPipeline pipeline = ch.pipeline();
        pipeline.addLast("httpServerCodec", new HttpServerCodec());
        pipeline.addLast("testHttpServerHandler", new TestHttpServerHandler());
    }
}
```


### TestHttpServerHandler编写

在同一个package中创建**TestHttpServerHandler**类,在该类中我们创建“Hello，World”字符串，然后当用户对服务器进行请求时，将Hello，World返回给用户。

**TestHttpServerHandler**需要继承**SimpleChannelInboundHandler** 类，并实现**channelRead0**方法。**channelread0** 读取客户端发送的请求，并向客户端返回响应的代码的函数。

我们用**ByteBuf**构建Hello，World字符串，**ByteBuf** 是Netty实现的最基本的数据缓冲。
```java
ByteBuf content = Unpooled.copiedBuffer("Hello, World", CharsetUtil.UTF_8);
```

然后用**DefaultFullHttpResponse**构建响应，该类接受的参数有：协议类型，返回状态，返回内容（即helloworld）。

然后我们对响应头进行设置，设置内容类型为text/plain，以及设置内容长度为Hello，World的长度。

最后用**ctx.writeAndFlush**方法把内容返回给客户端。

具体代码如下所示。
![New TestHttpServerHandler ](https://img-blog.csdnimg.cn/20190528091941804.png)
```java
public class TestHttpServerHandler extends SimpleChannelInboundHandler<HttpObject> {
    @Override
    protected void channelRead0(ChannelHandlerContext ctx, HttpObject msg) throws Exception {
        if (msg instanceof HttpRequest) {
            ByteBuf content = Unpooled.copiedBuffer("Hello, World", CharsetUtil.UTF_8);
            FullHttpResponse response = new DefaultFullHttpResponse(HttpVersion.HTTP_1_1, HttpResponseStatus.OK, content);
            response.headers().set(HttpHeaderNames.CONTENT_TYPE, "text/plain");
            response.headers().set(HttpHeaderNames.CONTENT_LENGTH, content.readableBytes());
            ctx.writeAndFlush(response);
        }

    }
}
```

### 运行Netty服务器

点击Run-> Run "TestServer"运行刚刚编写的程序。
![](https://i.imgur.com/dSm3huB.png)

打开浏览器，输入网址localhost:8888
可以看到服务器返回Hello，World


![](https://i.imgur.com/RkzCY9p.png)


至此，我们第一个netty服务器就编写成功了！
