/*
	���⿡�� ���̵� ����. ������ ���ϸ� �������� ������ ������ų �� ����.

	���� �ڽĵ��� �ʿ� ���� ������ �м��Ѵ�.
	
	���� ������ �ذ��� �Ұ����� ���� ������ ���� ���� ���� ������ ��ȯ�Ͽ� 
	�θ𿡰� ������ ��û�Ѵ�.

	���� �ڽſ��� �׿� ������ �ִٸ�, �̴� ���� ������ ��ȯ�Ͽ� �θ𿡰� ���� 
	������ ������ ����ϰ� �Ѵ�. (�ֳ��ϸ� ������ n���� �������ֱ� ����)

	�������� �䱸�ϴ� �̵� ȸ���� ���� �����̰� ���� �����̰� �����ϹǷ�
	���밪�� ���ؼ� �����ָ� �ȴ�.
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


