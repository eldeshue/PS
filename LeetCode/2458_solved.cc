
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

/*
#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
*/
#include <unordered_map>
class Solution
{
private:
	using pii = pair<int, int>;
	unordered_map<int, int> table;
	vector<pii> maxHeightPerDepth;
	void updatePii(pii &target, const int n)
	{
		if (target.first < n) // real max
		{
			target.second = target.first;
			target.first = n;
		}
		else if (target.second < n) // second max
			target.second = n;
		return;
	}
	int getValPii(const pii &target, const int n)
	{
		if (target.first == n)
			return target.second;
		return target.first;
	}
	int dfsSetHeight(const TreeNode *curNode, const int depth)
	{
		// base case
		if (curNode == nullptr)
			return -1;
		// prepare cache to save max height per depth
		if (maxHeightPerDepth.size() == depth)
			maxHeightPerDepth.push_back({-1, -1});
		// get height of childen subtree
		const int curHeight = max(dfsSetHeight(curNode->left, depth + 1),
								  dfsSetHeight(curNode->right, depth + 1)) +
							  1;
		table.insert(make_pair(curNode->val, curHeight));
		// update pii per depth
		updatePii(maxHeightPerDepth[depth], curHeight);
		// return my height
		return curHeight;
	}
	void dfsSetTable(const TreeNode *curNode, const int depth)
	{
		if (curNode == nullptr)
			return;
		// set table
		table[curNode->val] = depth + getValPii(maxHeightPerDepth[depth], table[curNode->val]);
		//
		dfsSetTable(curNode->left, depth + 1);
		dfsSetTable(curNode->right, depth + 1);
	}

public:
	// solution method
	vector<int> treeQueries(TreeNode *root, vector<int> &queries)
	{
		// set table
		dfsSetHeight(root, 0);
		dfsSetTable(root, 0);
		// handle query
		vector<int> result;
		for (const int q : queries)
			result.push_back(table[q]);
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
