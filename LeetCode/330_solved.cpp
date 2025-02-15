
#include <iostream>
#include <vector>

using namespace std;

// solution class
/*
	Ǯ�� ����

	0. �ٽ� ���� completeRange
	completeRange ������ �κ����� ���ؼ� Ŀ�� ������ ������ �ǹ���.
	�� ������ ���� n�̻��� �� �� ���� �����ϰ�, �� ������ �ʿ��� ��ġ�� Ƚ���� ����.

	1. Ȯ���� ����
	�׷��ٸ� �ش� ������ Ȯ���ϴ� ������ �߿���.
	Ȯ���ϱ� ���� ������ ������ �߰��Ǵ� ���� �κ����� ���ؼ� ǥ�� ������ �������� ��.
	�� 1���� curNum - 1������ ��� ǥ�������ؾ� curNum�� �߰��� �� ����.

	���� ǥ���� �Ұ����� �κ��� �ִٸ�, patch�� ���ؼ� �Ų���� ��.
	�̷��� ��ġ�� �ʿ��� �κ��� hole�̶� �Ѵ�.

	2. ��ġ�� ���ؼ�
	��ġ�� ���ؼ� completeRange�� Ȯ���ϰ�, �̸� ���ؼ� curNum�� �޾Ƶ��� �� ����.
	�ּ� Ƚ���� patch�� �����ؾ� �ϹǷ�, �ּҺ������ completeRange �ִ�� Ȯ���ؾ� ��.

	�� ���� ��ġ�� �ִ��� Ȯ���� ��� ����� completeRange + 1�� �߰��ϴ� ����.
	�ֳ��ϸ� �̹� 1���� completeRange������ �Ϻ��ϰ� cover�ϰ� �ֱ� ������.
*/
class Solution
{
public:
	// solution method
	int minPatches(vector<int>& nums, int n)
	{
		long long completeRange = 0;
		int numPatch = 0;
		for (const int& curNum : nums)
		{
			// if there is a whole between current range and added number, add patch.
			while (completeRange < curNum - 1 && completeRange < n)
			{
				// setting patch
				// patched number will be (completeRange + 1)
				numPatch++;
				completeRange = 2 * completeRange + 1;
			}
			completeRange += curNum;
			if (completeRange >= n)
				break;
		}
		// after all, still there is a whole,
		// add patches
		while (completeRange < n)
		{
			numPatch++;
			completeRange = 2 * completeRange + 1;
		}
		return numPatch;
	}
	//
};

// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}

