
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
#include <unordered_map>
#include <vector>
class Solution
{
private:
	using ll = long long;
	vector<ll> sumOfDepth;
	void dfs1(TreeNode *curNode, const int depth)
	{
		if (curNode == nullptr)
			return;
		if (sumOfDepth.size() == depth)
			sumOfDepth.push_back(0);
		sumOfDepth[depth] += curNode->val;
		dfs1(curNode->left, depth + 1);
		dfs1(curNode->right, depth + 1);
	}
	void dfs2(TreeNode *curNode, const ll brotherSum, const int depth)
	{
		if (curNode == nullptr)
			return;
		// get brother value
		curNode->val = sumOfDepth[depth] - brotherSum;
		const ll nextSum = [&]()
		{
			ll result = 0;
			if (curNode->left != nullptr)
				result += curNode->left->val;
			if (curNode->right != nullptr)
				result += curNode->right->val;
			return result;
		}();
		dfs2(curNode->left, nextSum, depth + 1);
		dfs2(curNode->right, nextSum, depth + 1);
	}

public:
	// solution method
	TreeNode *replaceValueInTree(TreeNode *root)
	{
		dfs1(root, 0);
		if (root != nullptr)
			dfs2(root, root->val, 0);
		return root;
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
