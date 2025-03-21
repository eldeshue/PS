
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

#include <unordered_map>	// for prefix sum
#include <stack>

// range : half open [ start, end ]
void delete_range(ListNode *start, ListNode *end)
{
	if (start != nullptr && start != end)
	{
		delete_range(start->next, end);
	}
	delete start;
	return;
}

class Solution
{
public:
	ListNode* removeZeroSumSublists(ListNode* head)
	{
		// pair < sum, node >
		unordered_map<int, ListNode *> prefixSum;
		stack<int> prevSums;
		ListNode *curNode = head;
		int curSum = 0;

		while (curNode != nullptr)
		{
			ListNode *nextNode = curNode->next;
			curSum += curNode->val;
			if (curSum == 0)	// current sum zero
			{
				delete_range(head, curNode);
				head = nextNode;
				while (!prevSums.empty())
				{
					prefixSum.erase(prevSums.top());
					prevSums.pop();
				}
			}
			else if (prefixSum.find(curSum) != prefixSum.end())
			{
				ListNode *&prevNode = prefixSum[curSum];
				delete_range(prevNode->next, curNode);
				prevNode->next = nextNode;
				// delete prefixSum using stack
				while (prevSums.top() != curSum)
				{
					prefixSum.erase(prevSums.top());
					prevSums.pop();
				}
			}
			else
			{
				prevSums.push(curSum);
				prefixSum.insert(make_pair(curSum, curNode));
			}
			curNode = nextNode;
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
