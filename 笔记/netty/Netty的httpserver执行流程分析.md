## Netty的httpserver执行流程分析

在[上一篇文章](https://blog.csdn.net/qq_31027515/article/details/90613839)，我们用Netty进行了一个建议的HttpServer的编写，在本文，我们对该server的执行流程做简要的分析。

### 回调函数介绍

我们在上一节编写的TestHttpServerHandler类是继承SimpleChannelInboundHandler类，该类是专门对客户端发送请求进行处理的类。通过观察源码，我们发现该类又继承了ChannelInboundHandlerAdapter类。
![SimpleChannelInboundHandler源码](https://img-blog.csdnimg.cn/20190528221704693.png)

ChannelInboundHandlerAdapter类中有很多回调函数，例如handlerAdded，channelActive，channelInactive，channelRegisteredchannelUnregistered等函数。这些函数分别是在handler被加入时，channel被注册和取消注册时以及channel被激活时由Netty框架进行调用。
我们在TestServerInitializer类中覆盖这五个方法，如下所示。
```java
    @Override
    public void channelActive(ChannelHandlerContext ctx) throws Exception {
        System.out.println("channel active");
        super.channelActive(ctx);
    }
```
```java
    @Override
    public void channelInactive(ChannelHandlerContext ctx) throws Exception {
        System.out.println("channel inactive");
        super.channelInactive(ctx);
    }
```

```java
    @Override
    public void channelRegistered(ChannelHandlerContext ctx) throws Exception {
        System.out.println("channel registered");
        super.channelRegistered(ctx);
    }
```
```java
    @Override
    public void channelUnregistered(ChannelHandlerContext ctx) throws Exception {
        System.out.println("channel unregistered");
        super.channelUnregistered(ctx);
    }
```
```java
    @Override
    public void handlerAdded(ChannelHandlerContext ctx) throws Exception {
        System.out.println("handler added");
        super.handlerAdded(ctx);
    }
```

### curl命令和浏览器之间的表现差异

然后我们用curl命令对服务器进行请求看看服务器终端中会出现什么结果：

![curl](https://img-blog.csdnimg.cn/20190528223100997.png)

服务器返回结果如下所示：

![服务器返回](https://img-blog.csdnimg.cn/20190528223109169.png)

可以看到server的执行流程是按照如下五步进行的。

1. handler added
2. channel registered
3. channel active
4. channel inactive
5. channel unregistered

但是如果我们用浏览器（Chrome）对服务器进行请求时，却发现命令行返回结果如下图所示。

![浏览器请求](https://img-blog.csdnimg.cn/20190528223605947.png)
在该图中，每一步都执行了两次，并且没有channel inactive和channel unregistered输出，这是为什么呢？

打开google开发者工具，点击Network，我们可以看到，浏览器不仅请求了localhost根目录，还请求了favicon.ico文件，所以一共执行了两个请求，所以每一步都执行了两次。

（注意不同浏览器请求不同，比如说Firefox中就不会请求localhost两次）

![chrome流量](https://img-blog.csdnimg.cn/20190528223839253.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMxMDI3NTE1,size_16,color_FFFFFF,t_70)

当我们关闭Chrome标签时，终端输出了如下信息。

![浏览器关闭](https://img-blog.csdnimg.cn/2019052822361333.png)
所以我们知道在浏览器打开localhost的时候请求一直都保持连接，所以不会输出channel inactive和channel unregistered。

而因为curl是网络命令工具，在curl请求完之后，请求就关闭掉了，所以会直接输出channel inactive和channel unregistered信息。

如果是spring MVC框架，在处理完请求返回给用户之后，Tomcat会保证响应的连接会自动关闭掉。但是Netty需要自己做，需要自己写代码令服务器端主动关闭连接。

需要在channelRead0函数末尾加上*ctx.channel().close();*代码
```java
    protected void channelRead0(ChannelHandlerContext ctx, HttpObject msg) throws Exception {
        if (msg instanceof HttpRequest) {

            ByteBuf content = Unpooled.copiedBuffer("Hello, World", CharsetUtil.UTF_8);
            FullHttpResponse response = new DefaultFullHttpResponse(HttpVersion.HTTP_1_1, HttpResponseStatus.OK, content);
            response.headers().set(HttpHeaderNames.CONTENT_TYPE, "text/plain");
            response.headers().set(HttpHeaderNames.CONTENT_LENGTH, content.readableBytes());
            ctx.writeAndFlush(response);
            ctx.channel().close();
        }

    }
```









