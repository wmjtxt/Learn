剑指offer解题思路
====
<details>
<summary>1 二维数组中的查找</summary>

* 题目描述

在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

* 解题思路

二维数组可以看成一个m\*n的矩阵。

根据所给的条件，可以从矩阵的左下角开始访问，判断数组元素与目标数据的大小。

时间复杂度为O(n)。

* 代码实现

```c
class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        int m = array.size();
        int n = array[0].size();
        for(int i = m-1, j = 0; i >= 0 && j < n;){
            if(array[i][j] == target){
                return true;
            }
            else if(array[i][j] < target){
                j++;
            }
            else{
                i--;
            }
        }
        return false;
    }
};
```
</details>

<details>
<summary>2 替换空格</summary>
* 题目描述

请实现一个函数，将一个字符串中的每个空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。

* 解题思路

从后往前替换

* 代码实现
```c
class Solution {
public:
	void replaceSpace(char *str,int length) {
        int spacenum = 0;
        for(int i = 0; i < length; i++)
        {
            if(str[i] == ' ')
                spacenum++;
        }
        int newlen = length + 2*spacenum;
        int oldlen = length;
        length = newlen;
        while(oldlen >= 0)
        {
            if(str[oldlen] == ' ')
            {
                str[newlen--] = '0';
                str[newlen--] = '2';
                str[newlen--] = '%';
            }
            else
            {
                str[newlen--]=str[oldlen];
            }
            oldlen--;
        }
	}
};
```

</details>

<details>
<summary>3 从尾到头打印链表</summary>
* 题目描述
输入一个链表，按链表值从尾到头的顺序返回一个ArrayList
* 解题思路
递归
* 代码实现
```c
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> res;
		if(head != NULL){
			if(head->next != NULL){
				res = printListFromTailToHead(head->next);
			}
			res.push_back(head->val);
		}
		return res;
    }
};
```

</details>

<details>
<summary>4 重建二叉树</summary>
* 题目描述
输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
* 解题思路
递归
* 代码实现
```c

```

</details>

<details>
<summary>5 </summary>
* 题目描述
* 解题思路
* 代码实现
```c

```

</details>
