
#include <iostream>
#include <string>

using namespace std;

// solution class
/*
	Pelindromic Substring.

	�־��� ���ڿ� ������ �縰����� ���� ���ڿ��� ������ ã�´�.

	solution
	�����̵� ������� dp�� �����Ѵ�.
	������ ����� ���� ���ڿ��� ���̷� ���, ���ڿ��� ũ�⸶�� �����̵� �����츦 ����.
	��, dp�� �����Ͽ� �׻� �� ���ܸ� �߰��� Ȯ���ϰ�, �� ���δ� ĳ���ص� ����� �̿���.

	�̴� �縰��� ���ڿ��� Ư�� ��, �縰��� ���ڿ��� �� ���� ������ ���ڸ� �߰��ϸ� 
	�״�� ���ο� �縰����� ���� �� �ֱ� ������.
*/

class Solution
{
private:
	bool cache[1000][1000];	// memory for dp
public:
	// solution method
	// count number of pelindrome substring.
	int countSubstrings(string s)
	{
		int cnt = 0;
		// sliding window with DP
		for (int winSize = 0; winSize < s.size(); ++winSize)
		{
			for (int start = 0; start < s.size() - winSize; ++start)
			{
				int end = start + winSize;
				if (s[start] == s[end])
				{
					if (end - start <= 1 || cache[start + 1][end - 1] == true)
					{
						cache[start][end] = true;
						cnt++;
					}
				}
			}
		}
		return cnt;
	}
	//
};

// solution class

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Solution test;
	string str1 = "abc";
	cout << test.countSubstrings(str1) << '\n';
	string str2 = "aaa";
	cout << test.countSubstrings(str2) << '\n';
}