
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

ListNode* removeNextNNode(ListNode *curNode, int cnt)
{
	ListNode *finalNode = nullptr;

	if (cnt != 0)
		finalNode = removeNextNNode(curNode->next, cnt - 1);
	else
		return curNode;
	delete curNode;
	return finalNode;
}

class Solution
{
public:
	ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode *list2)
	{
		ListNode *endNode, *curNode = list1;

		for (int i = 0; i < a - 1; ++i)
		{
			curNode = curNode->next;
		}
		endNode = removeNextNNode(curNode->next, b - a + 1);
		curNode->next = list2;
		curNode = list2;
		while (curNode->next != nullptr)	// get end of list2
		{
			curNode = curNode->next;
		}
		curNode->next = endNode;
		return list1;
	}
};

// solution
// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}
