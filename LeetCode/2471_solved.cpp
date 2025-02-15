

#include <iostream>

using namespace std;

// solution class
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <unordered_map>
#include <queue>
#include <algorithm>
class Solution
{
private:
	using pti = pair<TreeNode*, int>;
public:
	// solution method
	int minimumOperations(TreeNode* root)
	{
		unordered_map<int, int> wrongPos;
		queue<TreeNode*> q;
		queue<pti> q2;

		//
		int lastIdx = 0;
		int prevLevel = 0;
		vector<int> sortedValues;
		q2.push(make_pair(root, 1));
		while (!q2.empty())
		{
			TreeNode* curNode = q2.front().first;
			const int curLevel = q2.front().second;
			if (prevLevel != curLevel)
			{
				// sort level
				sort(sortedValues.begin() + lastIdx, sortedValues.end());
				lastIdx = sortedValues.size();
			}
			prevLevel = curLevel;
			q2.pop();
			sortedValues.push_back(curNode->val);
			if (curNode->left != nullptr)
				q2.push(make_pair(curNode->left, curLevel + 1));
			if (curNode->right != nullptr)
				q2.push(make_pair(curNode->right, curLevel + 1));
		}
		sort(sortedValues.begin() + lastIdx, sortedValues.end());

		// bfs
		int curIdx = 0, result = 0;
		q.push(root);
		while (!q.empty())
		{
			TreeNode* curNode = q.front();
			q.pop();
			if (sortedValues[curIdx] != curNode->val)
				wrongPos.insert(make_pair(sortedValues[curIdx], curNode->val));
			if (curNode->left != nullptr)
				q.push(curNode->left);
			if (curNode->right != nullptr)
				q.push(curNode->right);
			++curIdx;
		}

		// result count
		while (!wrongPos.empty())
		{
			int curVal, nextVal, cnt = 1;
			tie(curVal, nextVal) = *(wrongPos.begin());
			wrongPos.erase(curVal);
			while (wrongPos.find(nextVal) != wrongPos.end())
			{
				curVal = nextVal;
				nextVal = wrongPos[curVal];
				wrongPos.erase(curVal);
				cnt++;
			}
			result += cnt - 1;
		}
		return result;
	}
	//
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();
	// solution class

	int main()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);

		Solution test;
	}
