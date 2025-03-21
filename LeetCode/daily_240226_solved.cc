
#include <iostream>

using namespace std;


 // Definition for a binary tree node.
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// solution
class Solution
{
public:
	Solution()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
	}
	bool isSameTree(TreeNode* p, TreeNode* q)
	{
		// check value
		if (p == q)
			return true;
		if ((p == nullptr) || (q == nullptr)
		|| (p->val != q->val)
		|| (p->left == nullptr && q->left != nullptr)
		|| (p->left != nullptr && q->left == nullptr)
		|| (p->right == nullptr && q->right != nullptr)
		|| (p->right != nullptr && q->right == nullptr))
			return false;
		// dfs
		return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
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
