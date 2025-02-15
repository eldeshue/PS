
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")

class Solution
{
public:
	// solution method
	bool canBeValid(string s, string locked)
	{
		const int N = s.size();

		if (N & 1)
			return false;
		// lock �� position�� value�� �����ϰ� ��� �� �ٲ� �� ����
		// �ٲٴ� Ƚ���� �߿��� ������ �ƴ϶� lock �̿��� ���� �ǹ̰� ����
		// ���� lock�� ��ġ�� ���� �߿���

		// ������ lock�� ��ġ�� ��ȣ�� ������ balance ���θ� Ȯ���ϴ� ����
		// Ȯ���� ��ȣ�� ������ �������� balance�ϰ� �ٲ� �� �ִ��� ���θ� Ȯ��
		int lCnt = 0, rCnt = 0;
		for (int i = 0; i < N; ++i)
		{
			if (locked[i] == '1' && s[i] == ')')
			{
				// ���� �� left to right�ϰ� ')'�� count
				// ')'�� ���� ��ġ�� �������� ���� �̻��̶��
				// ���� ��θ� '('�� �ٲ㵵 balance�� ã�� �� ����
				rCnt++;
				if (rCnt > (i + 1) / 2)
					return false;
			}
		}
		for (int i = N - 1; i >= 0; --i)
		{
			// ���������� ������ �õ��ص� unbalance�ؼ� Ǯ�̰� �Ұ�����
			if (locked[i] == '1' && s[i] == '(')
			{
				lCnt++;
				if (lCnt > (N - i) / 2)
					return false;
			}
		}
		return true;
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


