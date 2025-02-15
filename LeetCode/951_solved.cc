
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
class Solution
{
public:
	bool flipEquiv(TreeNode *root1, TreeNode *root2)
	{
		// dfs together
		if (root1 == nullptr && root1 == root2)
			return true;
		if (root1 == nullptr || root2 == nullptr || root1->val != root2->val)
			return false;
		// filp, both are not nullptr
		// O(N).
		return (flipEquiv(root1->left, root2->left) && flipEquiv(root1->right, root2->right)) || (flipEquiv(root1->left, root2->right) && flipEquiv(root1->right, root2->left));
	}
};
