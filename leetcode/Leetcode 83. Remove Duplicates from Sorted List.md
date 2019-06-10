@[TOC](Leetcode 83. Remove Duplicates from Sorted List 删除排序链表中的重复元素)

## 1. Two Sum 
### 题目描述
Given a sorted linked list, delete all duplicates such that each element appear only once.

### 示例:
Example 1:

    Input: 1->1->2
    Output: 1->2

Example 2:

    Input: 1->1->2->3->3
    Output: 1->2->3

### 解答1

第一种解法是常规解法，考察链表操作。设两个指针**prev**, **curr**；**prev**指向前一个节点，**curr**指向当前节点。

当**prev**的值等于**curr**的值时令**prev->next = curr -> next**，更新**curr**的值。

否则**curr = curr -> next**，**prev = prev -> next**。

### 代码1
```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if( head == NULL)
            return head;
        ListNode* curr = head -> next;
        ListNode* prev = head;
        while(curr != NULL) {
            if (curr -> val == prev -> val) {
                prev -> next = curr -> next;
                curr = curr -> next;
            }
            else {
            curr = curr -> next;
            prev = prev -> next;                
            }
        }
    return head;
    }
    
};
```

### 解答2

第二种解法是递归操作，先判断递归结束条件。

然后递归求解**head -> next**，查看返回结果的**val**和**head**是否相同。

如果相同**head -> next = next -> next**，否则**head -> next = next**。

### 代码2
```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL || head -> next == NULL)
            return head;
        auto next = deleteDuplicates(head -> next);
        if (head -> val == next -> val) {
            head -> next = next -> next;
        }
        else 
            head -> next = next;
    return head;
    }
    
};
```