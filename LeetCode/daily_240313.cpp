
#include <iostream>

using namespace std;

struct ListNode
{
	int val;
	ListNode* next;
};

// solution class
#include <array>

using node = pair<ListNode*, int>;	// node, sum 

class Solution
{
public:
	// solution method
	ListNode* removeZeroSumSublists(ListNode* head)
	{
		array<node, 1000> nodes;
		ListNode* curNode = head;
		ListNode* returnHeadNode = head;
		int last_pos = 0;

		while (curNode != nullptr)
		{
			if (curNode->val == 0)
			{
				if (curNode == returnHeadNode)
					returnHeadNode = curNode->next;
				else
					nodes[last_pos - 1].first->next = curNode->next;
				delete curNode;
				continue;
			}
			// update accum sum
			nodes[last_pos] = make_pair(curNode, curNode->val);
			for (int i = 0; i < last_pos; ++i)
			{
				nodes[i].second += curNode->val;
				if (nodes[i].second == 0)	// sum is zero
				{
					// make new connection
					if (i == 0)
						returnHeadNode = curNode;
					else
						nodes[i - 1].first->next = curNode->next;
					// delete between
					for (int j = i; j <= last_pos; ++j)
						delete (nodes[j].first);
					// update last_pos
					last_pos = i - 1;
					curNode = nodes[last_pos - 1].first;
				}
			}
			last_pos++;
			curNode = curNode->next;
		}
		return returnHeadNode;
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

