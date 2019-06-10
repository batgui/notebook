


@[TOC](Leetcode 82. Remove Duplicates from Sorted List II 删除排序链表中的重复元素 II)

## 1. Two Sum 
### 题目描述
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.



### 示例:

Example 1:

	Input: 1->2->3->3->4->4->5
	Output: 1->2->5

Example 2:

	Input: 1->1->1->2->3
	Output: 2->3	
### 解答1

这道题和[Leetcode 83. Remove Duplicates from Sorted List](https://blog.csdn.net/qq_31027515/article/details/90742849)类似。

因为要删掉所有重复的点，为了方便起见我们先设定一个fakeHead，令fakeHead -> next = head。

令prev指向上个节点，curr指向当前节点。

注意，当出现了重复节点的时候，我们需要令prev -> next = curr -> next，当不出现重复节点的时候prev = prev -> next，判断的依据是prev = prev -> next，也就是prev指向的下一个节点是否为当前节点。

### 代码1
```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
    	if (head == NULL)
    		return head;
        ListNode* fakeHead = new ListNode(0);
        fakeHead -> next = head;

        ListNode* curr = fakeHead -> next;
    	ListNode* prev = fakeHead;
       while(curr -> next != NULL) {
  			while( curr -> next != NULL && curr -> val == curr -> next -> val)
  				curr = curr -> next;
  			if ( prev -> next == curr ) {
  				prev = prev -> next;
  			}
  			else {
  				prev -> next = curr -> next;
  			}
  			curr = curr -> next;
        }
    return fakeHead -> next;
    }
};
```

### 解答2

这题也可以用递归来做，先判断递归结束条件。

当出现重复节点的时候 直接返回deleteDuplicates递归后的结果。

当不出现时，先令head -> next等于deleteDuplicates递归后的结果，然后返回head。

### 代码2
```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL || head -> next == NULL)
        	return head;
        auto curr = head;
        while (curr -> next != NULL && curr ->val == curr -> next -> val) {
        	curr = curr -> next;

        }
        if (head  == curr) {
        	head -> next = deleteDuplicates(curr -> next);
        	return head;
        }
        else 
        	return deleteDuplicates(curr -> next);
    }
};
```
