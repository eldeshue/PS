
#include <iostream>
#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

using namespace std;

// solution class
#include <stack>

class Solution
{
public:
	// solution method
	void reorderList(ListNode* head)
	{
		stack<ListNode*> nodeStack;
		ListNode *curNode = head, *nextNode = head->next;
		int len = 1;
		while (curNode != nullptr)
		{
			len++;
			curNode = curNode->next;
		}
		//
		curNode = head, nextNode = head->next;
		for (int i = 0; i < (len / 2); ++i)
		{
			curNode = curNode->next;
		}
		if (len & 1)
		{
			curNode = curNode->next;
		}
		for (int i = 0; i < (len / 2); ++i)
		{
			nodeStack.push(curNode);
			curNode = curNode->next;
		}
		//
		curNode = head, nextNode = head->next;
		for (int i = 0; i < len / 2; ++i)
		{
			curNode->next = nodeStack.top();
			curNode->next->next = nextNode;
			nodeStack.pop();
			curNode = nextNode;
			nextNode = nextNode->next;
		}
		curNode->next = nullptr;
	}
	//
};

// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}