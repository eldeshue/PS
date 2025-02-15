
#include <iostream>
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
// solution
#include <vector>
#include <functional>
class Solution
{
public:
	// solution method
	TreeNode *balanceBST(TreeNode *root)
	{
		// collect values in inorder traversal
		vector<int> values;

		std::function<void(TreeNode *)> f = [&](TreeNode *curNode)
		{
			if (curNode->left != nullptr)
				f(curNode->left);
			values.push_back(curNode->val);
			if (curNode->right != nullptr)
				f(curNode->right);
		};
		f(root);

		// build perfect binary tree with size n
		const int N = values.size();
		int idx = 0;
		vector<TreeNode *> resultTree(N);
		std::function<void(TreeNode *)> f1 = [&](TreeNode *curNode)
		{
			if (curNode->left != nullptr)
				f1(curNode->left);
			resultTree[idx++] = curNode;
			if (curNode->right != nullptr)
				f1(curNode->right);
		};
		f1(root);
		for (int i = 0; i < N; ++i)
		{
			int left = 2 * (i + 1);
			int right = 2 * (i + 1) + 1;

			if (left <= N)
				resultTree[i]->left = resultTree[left - 1];
			else
				resultTree[i]->left = nullptr;
			if (right <= N)
				resultTree[i]->right = resultTree[right - 1];
			else
				resultTree[i]->right = nullptr;
		}

		// initialize binary tree with collected values
		idx = 0;
		std::function<void(TreeNode *)> f2 = [&](TreeNode *curNode)
		{
			if (curNode->left != nullptr)
				f2(curNode->left);
			curNode->val = values[idx++];
			if (curNode->right != nullptr)
				f2(curNode->right);
		};
		f2(resultTree[0]);

		// return root of balanced binary tree
		return resultTree[0];
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
