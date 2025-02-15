
#include <iostream>

using namespace std;

struct ListNode
{
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <vector>
class Solution
{
private:
	vector<int> t;
	vector<int> w;
	void failure_function()
	{
		int pos = 1;
		int cnd = 0;

		t[0] = -1;
		while (pos < w.size())
		{
			if (w[pos] == w[cnd]) // match
			{
				t[pos] = t[cnd];
			}
			else // mismatch
			{
				t[pos] = cnd;
				while (0 <= cnd && w[pos] != w[cnd]) // fall back during mismatch
					cnd = t[cnd];					 // cmd == -1 means no go back
			}
			pos++;
			cnd++;
		}
		t[pos] = cnd;
	};

	bool dfs(TreeNode *curNode, int wIdx)
	{
		bool result = false;
		if (curNode != nullptr)
		{
			const int &s = curNode->val;
			while (true)
			{
				if (s == w[wIdx]) // match
				{
					wIdx++;
					if (wIdx == w.size()) // occurence found
					{
						return true;
					}
				}
				else
				{
					// mis match, jump wIdx back
					wIdx = t[wIdx];
					if (wIdx < 0) // -1 means there is no going back
					{
						wIdx++;
						break;
					}
				}
			}
			// dfs search
			result = dfs(curNode->left, wIdx);
			if (result)
				return result;
			result = dfs(curNode->right, wIdx);
		}
		return result;
	}

public:
	bool isSubPath(ListNode *head, TreeNode *root)
	{
		while (head != nullptr)
		{
			w.push_back(head->val);
			head = head->next;
		}
		t.resize(w.size() + 1);
		failure_function();
		return dfs(root, 0);
	}
};
