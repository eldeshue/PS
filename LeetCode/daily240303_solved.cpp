
#include <iostream>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
};

// solution class

class Solution
{
public:
	Solution()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
	}
	// solution method
	ListNode* removeNthFromEnd(ListNode* head, int n)
	{
		ListNode* prev, * fast = head, * slow = head;
		int endPos = 0;

		for (int i = 0; i < n; ++i)
		{
			fast = fast->next;
		}
		while (fast != nullptr)
		{
			fast = fast->next;
			prev = slow;
			slow = slow->next;
		}
		if (slow == head)
		{
			ListNode* result = slow->next;
			delete slow;
			return result;
		}
		prev->next = slow->next;
		delete slow;
		return head;
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


