

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
#include <algorithm>
#include <vector>
#include <functional>
class Solution
{
private:
	using ll = long long;

public:
	long long kthLargestLevelSum(TreeNode *root, int k)
	{
		std::vector<ll> levelSum;

		// collect sum during dfs
		function<void(const TreeNode *, int)> dfs = [&](const TreeNode *curNode, const int level)
		{
			if (curNode == nullptr)
				return;
			if (levelSum.size() == level)
				levelSum.push_back(0);
			levelSum[level] += curNode->val;
			dfs(curNode->left, level + 1);
			dfs(curNode->right, level + 1);
		};
		dfs(root, 0);
		// exception handling
		if (levelSum.size() < k)
			return -1;
		// sort
		sort(levelSum.begin(), levelSum.end(), greater<ll>());
		// get kth sum
		return levelSum[k - 1];
	}
};

auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();
//
