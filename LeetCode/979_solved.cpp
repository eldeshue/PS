/*
	대출에서 아이디어를 얻음. 대출을 통하면 음수개의 코인을 성립시킬 수 있음.

	먼저 자식들의 필요 코인 개수를 분석한다.
	
	만약 스스로 해결이 불가능한 노드는 부족한 코인 수를 음의 값으로 반환하여 
	부모에게 대출을 요청한다.

	만약 자신에게 잉여 코인이 있다면, 이는 양의 값으로 반환하여 부모에게 있을 
	코인의 부족을 대비하게 한다. (왜냐하면 개수가 n으로 정해져있기 때문)

	문제에서 요구하는 이동 회수는 음의 코인이건 양의 코인이건 동일하므로
	절대값을 취해서 세어주면 된다.
*/
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
// solution class
class Solution {
private:
	int totalMoveCnt;
	int moveCoins(TreeNode* curNode)
	{
		int curCnt = curNode->val;
		int leftCnt = 0; int rightCnt = 0;
		if (curNode->left != nullptr)
			leftCnt = moveCoins(curNode->left);
		if (curNode->right != nullptr)
			rightCnt = moveCoins(curNode->right);
		totalMoveCnt += abs(leftCnt) + abs(rightCnt);
		curCnt += leftCnt + rightCnt;
		curNode->val = 1;
		return curCnt - 1;
	}
public:
	int distributeCoins(TreeNode* root) 
	{
		totalMoveCnt = 0;
		moveCoins(root);
		return totalMoveCnt;
	}
};
// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}


