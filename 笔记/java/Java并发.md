# Java实现并发的几种方法

Java程序默认以单线程方式运行。

## synchronized

Java 用过synchronized 关键字来保证一次只有一个线程在执行代码块。

```java
public synchronized void code() {
    // TODO
}
```

## Volatile

Volatile 关键字保证任何线程在读取Volatile修饰的变量的时候，读取的都是这个变量的最新数据。

## Threads 和 Runnable
```java
public class MyRunnable implements Runnable {

    @Override
    public void run() {
    	// TODO
    }
}
```

```java
import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) {


        Runnable task = new MyRunnable();
        Thread worker = new Thread(task);
        worker.setName('Myrunnable');
        worker.start();

}
```
创建thread会有很多overhead，性能低且不易管理

## Thread pools
```java
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    private static final int NUMOFTHREDS = 5;

    public static void main(String[] args) {
        ExecutorService executor = Executors.newFixedThreadPool(NUMOFTHREDS);
        for (int i = 0; i < 500; i++) {
            Runnable worker = new MyRunnable(10000000L + i);
            executor.execute(worker);
        }
        // executor不接受新的threads
        executor.shutdown();
        // 等待所有threads结束
        executor.awaitTermination();
        System.out.println("Finished all threads");
    }
}
```

## Futures 和 Callables

因为Runnable对象无法向调用者返回结果，我们可以用Callable类来返回结果。

```java
package de.vogella.concurrency.callables;

import java.util.concurrent.Callable;

public class MyCallable implements Callable<Long> {
    @Override
    public Long call() throws Exception {
		// TODO
		int sum = 1;
        return sum;
    }
}

```

```java

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class CallableFutures {
    private static final int NUMOFTHREDS = 5;

    public static void main(String[] args) {

        ExecutorService executor = Executors.newFixedThreadPool(NUMOFTHREDS);
        List<Future<Long>> list = new ArrayList<Future<Long>>();
        for (int i = 0; i < 10; i++) {
            Callable<Long> worker = new MyCallable();
            Future<Long> submit = executor.submit(worker);
            list.add(submit);
        }
        long sum = 0;
        for (Future<Long> future : list) {
            try {
                sum += future.get();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (ExecutionException e) {
                e.printStackTrace();
            }
        }
        System.out.println(sum);
        executor.shutdown();
    }
}
```
## CompletableFuture

CompletableFuture 在Future的基础上增加了异步调用的功能。callback()函数Thread执行结束的时候会自动调用。

CompletableFuture既支持阻塞，也支持非阻塞的callback()


```java
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;

public class CompletableFutureSimpleSnippet {
    public static void main(String[] args) {



        CompletableFuture<Integer>  data = createCompletableFuture()
                .thenApply((Integer count) -> {
                    int transformedValue = count * 10;
                    return transformedValue;
                });

            try {
              int count = futureCount.get();


             } catch (InterruptedException | ExecutionException ex) {
            }
    }

    private static CompletableFuture<Integer> createCompletableFuture() {
        CompletableFuture<Integer> futureCount = CompletableFuture.supplyAsync(
                () -> {
                    return 1;
                });
        return futureCount;
    }

}
```