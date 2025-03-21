
#include <iostream>

using namespace std;

struct ListNode
{
	int val;
	ListNode *next;
}

// solution
#pragma GCC optimize("03")
#pragma GCC target ("avx")

#include <unordered_set>

constexpr int VISITED = 2147483647;

class Solution
{
public:
	bool hasCycle(ListNode *head)
	{
		ListNode *pCurNode = head;

		while (pCurNode != nullptr)
		{
			if (pcurNode->val == VISITED)
				return true;
			pCurNode->val = VISITED;
			pCurNode = pCurNode->next;
		}
		return false;
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
