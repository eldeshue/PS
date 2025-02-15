

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
/*
// editorial code. so awsome
class Solution {
public:
	TreeNode* reverseOddLevels(TreeNode* root) {
		traverseDFS(root->left, root->right, 0);
		return root;
	}

private:
	// 거울 대칭 dfs, 서로 반대편 노드끼리 함께 dfs를 수행하며, 값을 swap함.
	// 재귀적으로 항상 거울 반대편 노드를 호출하기에 언제나 swap 가능함.
	void traverseDFS(TreeNode* leftChild, TreeNode* rightChild, int level) {
		if (leftChild == nullptr || rightChild == nullptr) return;
		// If the current level is odd, swap the values of the children.
		if (level % 2 == 0) swap(leftChild->val, rightChild->val);
		// 거울 대칭.
		traverseDFS(leftChild->left, rightChild->right, level + 1);
		traverseDFS(leftChild->right, rightChild->left, level + 1);
	}
};
*/

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <algorithm>
#include <functional>
#include <vector>
class Solution
{
private:
public:
	// solution method
public:
	using IOOP = function<void(int, TreeNode *)>;
	TreeNode *reverseOddLevels(TreeNode *root)
	{
		function<void(int, TreeNode *, IOOP)> dfsDo = [&](int nodeId, TreeNode *curNode, IOOP op) -> void
		{
			if (curNode != nullptr)
			{
				op(nodeId, curNode);
				dfsDo(2 * nodeId, curNode->left, op);
				dfsDo(2 * nodeId + 1, curNode->right, op);
			}
		};
		std::vector<int> heapTree;
		auto dfsRead = bind(dfsDo, placeholders::_1, placeholders::_2, [&](int nodeId, TreeNode *curNode)
							{
								if (nodeId >= heapTree.size())
								{
									heapTree.resize(2 * nodeId);
								}
								heapTree[nodeId] = curNode->val; });
		auto dfsWrite = bind(dfsDo, placeholders::_1, placeholders::_2, [&](int nodeId, TreeNode *curNode)
							 { curNode->val = heapTree[nodeId]; });

		// dfs, init heap tree
		dfsRead(1, root);
		// traverse and reverse heap tree
		for (int i = 1; (1 << i) < heapTree.size(); i += 2)
		{
			auto start = heapTree.begin() + (1 << i);
			auto end = heapTree.begin() + (1 << (i + 1));
			reverse(start, end);
		}
		// dfs, init tree
		dfsWrite(1, root);
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
