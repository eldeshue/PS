
/*
	주어진 이진트리에서 특정 노드를 지우고 그 결가 분리된 트리들, 즉 숲을 구하기

	새롭게 만들어진 숲에서 root가 되려면 다음의 두 조건을 만족해야 함.
		1. 고아여야 함. -> 즉 부모가 지워졌어야 가능
		2. 스스로는 살아있어야 함. -> 지워진 노드는 루트가 될 수 없음.

	이 두 조건을 바탕으로 트리를 dfs하며 값을 수집함.
*/
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
#include <functional>
#include <unordered_set>
class Solution
{
public:
	vector<TreeNode *> delNodes(TreeNode *root, vector<int> &to_delete)
	{
		vector<TreeNode *> result;
		unordered_set<int> toDelete(to_delete.begin(), to_delete.end()); // node to delete, unique
		function<bool(TreeNode *, bool)> dfs =
			[&](TreeNode *curNode, bool isOrphan) -> bool
		{
			// check self
			bool isDeleted = (toDelete.find(curNode->val) != toDelete.end());
			// check children, erase node
			bool isLeftDeleted = (curNode->left != nullptr && dfs(curNode->left, isDeleted));
			if (isLeftDeleted)
				curNode->left = nullptr;
			bool isRightDeleted = (curNode->right != nullptr && dfs(curNode->right, isDeleted));
			if (isRightDeleted)
				curNode->right = nullptr;
			// am i root? -> orphan, not deleted
			if (!isDeleted && isOrphan)
			{
				result.push_back(curNode);
			}
			return isDeleted;
		};
		dfs(root, true);
		return result;
	}
};
auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();
