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

using node = pair<TreeNode*, int>;

class Solution
{
public:
	Solution()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
	}
	int findBottomLeftValue(TreeNode* root)
	{
		queue<node> Q;
		// bfs, preorder

		int maxDepth = 0, lMostVal = root->val;
		Q.push(make_pair(root, 0));
		while (!Q.empty())
		{
			TreeNode*& curNode = Q.front().first;
			const int nextDepth = Q.front().second + 1;
			// left
			if (curNode->left != nullptr)
			{
				if (nextDepth > maxDepth)
				{
					maxDepth = nextDepth;
					lMostVal = curNode->left->val;
				}
				Q.push(make_pair(curNode->left, nextDepth));
			}
			// right
			if (curNode->right!= nullptr)
			{
				if (nextDepth > maxDepth)
				{
					maxDepth = nextDepth;
					lMostVal = curNode->right->val;
				}
				Q.push(make_pair(curNode->right, nextDepth));
			}
			Q.pop();
		}
		return lMostVal;
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
