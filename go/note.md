计算sha256
计算X的sha256的值
sha256.Sum256([]byte("X"))

go 格式化输出

%x输出16进制  %t输出二进制  %T输出值的类型


go在传递数组参数的时候也是值的拷贝，这和其他编程语言不一样。除非我们传递指针过去。
比如
```golang
func zero(ptr *[32]byte) 
```

我们通常传递slices而不是array

对于多个ifelse，我们通常用switch来判断。
```golang

		switch {
		case i >= len(a):
			count += popCount(b[i])
		case i >= len(b):
			count += popCount(a[i])
		default:
			count += popCount(a[i] ^ b[i])
		}

```

go没有while循环，需要用for模拟

```golang
	for ; b != 0; count++ {
		b &= b - 1
	}
```

go定义结构体以及结构体初始化
```golang

tests := []struct {
		a, b []byte
		want int
	}{
		{[]byte{0}, []byte{6}, 2},
		{[]byte{1, 2, 3}, []byte{4, 5, 6}, 7},
	}
```

如何将slice左移n位
```golang
s:= []int{0, 1, 2, 3, 4, 5}
reverse(s[:2])
reverse(s[2:])
reverse(s)
fmt.Println(s)
```
注意slice不能直接比较
当比较bytes的时候可以用bytes.equal比较
其他情况下需要自己写


定义空slice
```golang
var s = []int{}
```
判断slice是否为nil
```golang
if summer == nil
```
判断slice是否为空
```golang
if len(s) == 0
```
我们可以用make函数创建slice
```golang
make([]T, len)
make([]T, len, cap)
```
用append向slice里面添加items
```golang
var runes []rune
for _, r := range "Hello, 世界"
	runes = append(runes, r)
fmt.Println("")
```




