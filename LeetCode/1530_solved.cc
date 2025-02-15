
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
#include <string>
class Solution
{
private:
	int countDist(const std::string &p1, const std::string &p2)
	{
		int commonLen = 0;
		for (int i = 0; i < std::min(p1.size(), p2.size()); ++i)
		{
			if (p1[i] != p2[i])
				break;
			commonLen++;
		}
		return p1.size() + p2.size() - 2 * commonLen;
	}

	void dfs(const TreeNode *curNode, std::string &curPath, std::vector<std::string> &leaves, const int &maxDist, int &result)
	{
		if (curNode->left == nullptr && curNode->right == nullptr) // is leaf
		{
			// increase counter
			for (const std::string &l : leaves)
			{
				if (countDist(curPath, l) <= maxDist)
					result++;
			}
			// add new leaf
			leaves.push_back(curPath);
		}
		else
		{
			if (curNode->left != nullptr)
			{
				curPath.push_back('L');
				dfs(curNode->left, curPath, leaves, maxDist, result);
				curPath.pop_back();
			}
			if (curNode->right != nullptr)
			{
				curPath.push_back('R');
				dfs(curNode->right, curPath, leaves, maxDist, result);
				curPath.pop_back();
			}
		}
	}

public:
	int countPairs(TreeNode *root, int distance)
	{
		std::vector<std::string> leaves;
		std::string curPath;
		int result = 0;

		dfs(root, curPath, leaves, distance, result);
		return result;
	}
};
auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();

int main()
{
}
