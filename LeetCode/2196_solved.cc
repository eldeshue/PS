
// Definition for a binary tree node.
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

#include <unordered_map>
class Solution
{
public:
	TreeNode *createBinaryTree(vector<vector<int>> &descriptions)
	{
		const int numNode = descriptions.size();
		unordered_map<int, pair<TreeNode *, bool>> nodes;
		// bool value means isChild

		for (int i = 0; i < numNode; ++i)
		{
			const int &parent = descriptions[i][0];
			const int &child = descriptions[i][1];
			const int &isLeft = descriptions[i][2];
			// create node
			if (nodes.find(parent) == nodes.end())
			{
				nodes.insert(make_pair(parent, make_pair(new TreeNode(parent), false)));
			}
			if (nodes.find(child) == nodes.end())
			{
				nodes.insert(make_pair(child, make_pair(new TreeNode(child), true)));
			}
			// make link
			if (isLeft)
			{
				nodes[parent].first->left = nodes[child].first;
				nodes[child].second = true;
			}
			else
			{
				nodes[parent].first->right = nodes[child].first;
				nodes[child].second = true;
			}
		}
		TreeNode *root;
		for (const auto &entry : nodes)
		{
			auto &[key, val] = entry;
			auto &[node, isChild] = val;
			if (!isChild)
			{
				root = node;
				break;
			}
		}
		return root;
	}
};
