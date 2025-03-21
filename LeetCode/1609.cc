
/*
	2진  트리이므로, id로 힙의 인덱스를 부여하고 우선순위큐에 집어넣는다.

	11
	18                           14
	3          7                 null null
	null null  18       null
	            null 6

*/
#include <iostream>

using namespace std;

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
};

// solution
#include <queue>

using node = pair<int, TreeNode*>;	// first : depth, second : value

bool isSorted(bool isOdd, int prevVal, int curVal)
{
	if (isOdd)
	{
		return ((curVal & 1) == 1) && (prevVal < curVal);
	}
	else
	{
		return ((curVal & 1) == 0) && (prevVal > curVal);
	}
}

class Solution
{
public:
	Solution()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
	}
	bool isEvenOddTree(TreeNode* root)
	{
		int prevVal, prevLev;
		queue<node>Q;

		// level starts form 1, so even level has even value
		if ((root->val & 1) == 0)
			return false;
		prevLev = 0;
		prevVal = root->val;
		if (root->left != nullptr)
			Q.push(make_pair(2, root->left));
		if (root->right != nullptr)
			Q.push(make_pair(2, root->right));
		while (!Q.empty())
		{
			const int curLev = Q.front().first;
			const TreeNode *curNode = Q.front().second;
			const int& curVal = curNode->val;
			Q.pop();
			if (prevLev != curLev)	// change level
			{
				prevLev = curLev;
				if (curLev & 1)
					prevVal = 0;
				else
					prevVal = 2147483647;
			}
			if (!isSorted(curLev & 1, prevVal, curVal))
				return false;
			prevVal = curVal;
			// left
			if (curNode->left != nullptr)
				Q.push(make_pair(curLev + 1, curNode->left));
			// right
			if (curNode->right != nullptr)
				Q.push(make_pair(curLev + 1, curNode->right));
		}
		return true;
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
