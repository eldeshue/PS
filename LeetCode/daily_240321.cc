
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// solution
#pragma GCC optimize("03")
#pragma GCC target ("avx")

#include <stack>

class Solution
{
public:
    ListNode* reverseList(ListNode* head)
	{
		stack<ListNode *> nodeStack;
		ListNode *curNode = head;

		while (curNode != nullptr)
		{
			nodeStack.push(curNode);
			curNode = curNode->next;
		}
		head = nodeStack.top();
		curNode = head;
		while (!nodeStack.empty())
		{
			curNode->next = nodeStack.top();
			nodeStack.pop();
			curNode = curNode->next;
		}
		return head;
	}
};

// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}
