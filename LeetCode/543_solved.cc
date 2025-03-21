
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// solution
#include <unordered_map>
#include <queue>

class Solution
{
private:
	unordered_map<TreeNode*, TreeNode*> parentNode;
	TreeNode* bfsGetFarestFromRoot(TreeNode *rootNode)
	{
		queue<pair<TreeNode*, int>> Q;
		int max_depth = 0;
		TreeNode* farestNode = rootNode;

		Q.push(make_pair(rootNode, 0));
		while (!Q.empty())
		{
			TreeNode*& curNode = Q.front().first;
			const int& curDepth = Q.front().second;
			// left
			if (curNode->left != nullptr)
			{
				if (max_depth < curDepth + 1)
				{
					max_depth = curDepth + 1;
					farestNode = curNode->left;
				}
				parentNode.insert(make_pair(curNode->left, curNode));
				Q.push(make_pair(curNode->left, curDepth + 1));
			}
			// right
			if (curNode->right != nullptr)
			{
				if (max_depth < curDepth + 1)
				{
					max_depth = curDepth + 1;
					farestNode = curNode->right;
				}
				parentNode.insert(make_pair(curNode->right, curNode));
				Q.push(make_pair(curNode->right, curDepth + 1));
			}
			Q.pop();
		}
		return farestNode;
	}
	int dfsGetDiameter(TreeNode *curNode, TreeNode *prevNode)
	{
		int result = 0;

		// to parent
		if (parentNode.find(curNode) != parentNode.end()
			&& parentNode[curNode] != prevNode)
			result = max(result, 1 + dfsGetDiameter(parentNode[curNode], curNode));
		if (curNode->left != prevNode && curNode->left != nullptr)
			result = max(result, 1 + dfsGetDiameter(curNode->left, curNode));
		if (curNode->right != prevNode && curNode->right != nullptr)
			result = max(result, 1 + dfsGetDiameter(curNode->right, curNode));
		return result;
	}
public:
	Solution()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
	}
	int diameterOfBinaryTree(TreeNode* root)
	{
		// get farest node from root, name it startNode
		TreeNode *startNode = bfsGetFarestFromRoot(root);
		// get farest node from startNode
		// minimum 1
		return dfsGetDiameter(startNode, nullptr);
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
