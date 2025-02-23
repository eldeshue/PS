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

#include <stack>
#include <functional>
class Solution {
private:
public:
	TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
		// using stack, make preorder to postorder
		std::stack<int> st;
		int preIdx = 0, postIdx = 0;
		std::function<TreeNode* ()> dfs = [&](void) {
			st.push(preorder[preIdx++]);
			if (st.top() == postorder[postIdx])
			{
				st.pop();
				return new TreeNode(postorder[postIdx++]);
			}

			TreeNode* result = new TreeNode();
			// left
			if (st.top() != postorder[postIdx])
			{
				result->left = dfs();
			}
			else
			{
				st.pop();
				result->val = postorder[postIdx++];
				return result;
			}
			// right
			if (st.top() != postorder[postIdx])
			{
				result->right = dfs();
			}
			else
			{
				st.pop();
				result->val = postorder[postIdx++];
				return result;
			}
			// self
			st.pop();
			result->val = postorder[postIdx++];
			return result;
			};
		return dfs();
	}
};