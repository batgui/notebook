智能合约是一小段可以执行在以太坊区块链的代码。所有智能合约的代码都是公共可见的，且所有人都能调用智能合约的函数。


定义合约变量：

```sol
pragma solidity ^0.5.1;
contract MyContract {
    string value;

}
```

这个变量被称为state变量，每次我们写入这个变量的时候，变量都会被保存到blockchain中。因此这个变量被写入到storage中。

得到变量：
```sol
function get() public view returns(string){
	return value;
}
```

设置变量

```sol
function set(string memory _value) public {
	value = _value;
}
```

变量前面加_表明是局部变量。

为value变量用构造器设置默认值
```sol
constructor() public {
	value = "myValue";
}
```

不同类型的变量

```sol
bool public myBool = true;
int public myInt = false;
uint public myUint = false;
uint8 public myUint8 = false;
```
定义enum变量
```sol
enum State {Waiting, Ready, Active}
State public state;
```
我们可以在constructor中设置State的初始值

```sol
constructor() public {
	state = State.Waiting;
}

```
Structs
我们可以通过struct来定义自己需要的数据类型
```sol
struct Person {
	string _firstname;
	string _secondname;
} 

```
Arrays

```sol
Person[] public people;
```
通过调用people函数来得到特定的person
```sol
people(0);
```

向Person[]中添加person

```sol
function addPerson(string memory _firstname, string memory _secondname) {
	people.push(Person(_firstname, _secondname));
	peopleCount += 1;
}
```

modifier

```sol
    modifier inState(State _state) {
        require(
            state == _state,
            "Invalid state."
        );
        _;
    }
```



