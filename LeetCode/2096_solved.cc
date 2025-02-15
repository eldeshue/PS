
#include <iostream>
#include <vector>
#include <string>

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
#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <deque>
#include <functional>
class Solution
{
public:
	// solution method
	string getDirections(TreeNode *root, int startValue, int destValue)
	{
		string rootToStart, rootToDest, result;
		deque<char> curPath;

		function<void(TreeNode *)> dfs = [&](TreeNode *curNode) -> void
		{
			if (curNode->val == startValue)
			{
				for (const char &c : curPath)
				{
					rootToStart.push_back(c);
				}
			}
			else if (curNode->val == destValue)
			{
				for (const char &c : curPath)
				{
					rootToDest.push_back(c);
				}
			}
			//
			if (curNode->left != nullptr)
			{
				curPath.push_back('L');
				dfs(curNode->left);
				curPath.pop_back();
			}
			if (curNode->right != nullptr)
			{
				curPath.push_back('R');
				dfs(curNode->right);
				curPath.pop_back();
			}
		};
		dfs(root);

		// LCA
		int LCA = 0;
		while (rootToStart[LCA] == rootToDest[LCA])
		{
			LCA++;
		}
		// result set
		result.append(string(rootToStart.size() - LCA, 'U'));
		result.append(rootToDest.substr(LCA, -1));
		return result;
	}
};
auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
