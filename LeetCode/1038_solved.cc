
#include <iostream>
#include <vector>

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
#include <functional>
class Solution
{
public:
	// solution method
	// traverse tree, order of right -> mid -> left.
	TreeNode *bstToGst(TreeNode *root)
	{
		int sum = 0;
		std::function<void(TreeNode *)> f = [&](TreeNode *curNode)
		{
			// right
			if (curNode->right != nullptr)
				f(curNode->right);
			// mid
			curNode->val += sum;
			sum = curNode->val;
			// left
			if (curNode->left != nullptr)
				f(curNode->left);
		};
		f(root);
		return root;
	}
};

//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
