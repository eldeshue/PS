#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

//class Solution {
#include <unordered_set>
#include <functional>
class FindElements {
private:
	std::unordered_set<int> values;
public:
	FindElements(TreeNode* root) {
		std::function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int val) {
			values.insert(val);
			node->val = val;
			if (node->left != nullptr)
			{
				dfs(node->left, 2 * val + 1);
			}
			if (node->right != nullptr)
			{
				dfs(node->right, 2 * val + 2);
			}
			};
		dfs(root, 0);
	}

	bool find(int target) {
		return values.count(target);
	}
};