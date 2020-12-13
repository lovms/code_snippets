//Given the head of a linked list, remove the nth node from the end of the list and return its head.
//
//Follow up: Could you do this in one pass?
//
// 
//
//Example 1:
//
//
//Input: head = [1,2,3,4,5], n = 2
//Output: [1,2,3,5]
//Example 2:
//
//Input: head = [1], n = 1
//Output: []
//Example 3:
//
//Input: head = [1,2], n = 1
//Output: [1]
// 
//
//Constraints:
//
//The number of nodes in the list is sz.
//1 <= sz <= 30
//0 <= Node.val <= 100
//1 <= n <= sz
//通过次数289,367提交次数713,169
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 思路：
// 常用的List数据结构中的trick，一次遍历找到距离末尾距离n的节点,
// 使用双指针，先固定好它们之间的距离，然后同时往后迭代，直到第二个
// 指针达到了nullptr。

// 题目中给了很多限定，包括距离一定小于list的长度 ，所以很多边界条件
// 都不需要处理了，否则边界条件才是这类问题最大的难点，稍有不慎，就会访问
// 空指针，从而出core
#include <iostream>
#include <vector>

using std::vector;
/**
 * Definition for singly-linked list.*/
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 /**/
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* previous = head;
		ListNode* p1 = head->next;
		ListNode* p2 = head->next;
		while (n-- > 0) {
			p2 = p2->next;
		}

		while (p2 != nullptr) {
			previous = p1;
			p1 = p1->next;
			p2 = p2->next;
		}

		// delete p1
		previous->next = p1->next;
		delete p1;

		return head;
    }
};

/*
 * 这是AC的版本，head就是第一个List节点的指针
 * 而不像上面的那个版本，head是头，head->next才是真正的第一个节点
 * 
 * 所以在处理删除第一个节点上，需要注意，是不是删除了head节点，
 *
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
                ListNode* previous = head;
                ListNode* p1 = head;
                ListNode* p2 = head;
                while (n-- > 0) {
                        p2 = p2->next;
                }

                while (p2 != nullptr) {
                        previous = p1;
                        p1 = p1->next;
                        p2 = p2->next;
                }

                // delete p1
                if (p1 == head) { //要删除头节点了，所以赶紧转移
                    head = p1->next;
                } else {
                    previous->next = p1->next;
                }
                
                delete p1;

                return head;
    }
};
*/

class List {
public:
	List() : head(new ListNode(0)) {}
	void buildListFromVec(vector<int>& input) {
		for (int i = input.size()-1; i>=0; --i) {
			ListNode* nd = new ListNode(input[i]);
			nd->next = head->next;
			head->next = nd;
			head->val++;
		}
	}

	static void printList(List& l) {
		ListNode* p = l.head->next;
		while (p!=nullptr) {
			std::cout << p->val << " ";
			p = p->next;
		}
		std::cout << std::endl;
	}

	void destroyList() {
		ListNode* p = head;
		ListNode* q = p->next;
		while (p!=nullptr) {
			delete p;
			p = q;
			q = q->next;
		}
	}
public:
	ListNode* head;
};

int main() {
	// case 1:
	//vector<int> nums = {1,2,3,4,5};
	//int n = 2;
	
	// case 2:
	//vector<int> nums = {1};
	//int n = 1;

	// case 3:
	vector<int> nums = {1,2};
	int n = 1;

	List l;
	l.buildListFromVec(nums);
	List::printList(l);

	Solution s;
	s.removeNthFromEnd(l.head, n);

	ListNode* p = l.head->next;
	while (p!=nullptr) {
		std::cout << p->val << " ";
		p = p->next;
	}
	std::cout << std::endl;
	return 0;
}
