
#include <iostream>
#include <string>

using namespace std;

// solution class
/*
	Pelindromic Substring.

	주어진 문자열 내에서 펠린드롬인 서브 문자열의 개수를 찾는다.

	solution
	슬라이딩 윈도우와 dp를 종합한다.
	윈도우 사이즈를 서브 문자열의 길이로 삼고, 문자열의 크기마다 슬라이딩 윈도우를 수행.
	단, dp를 도입하여 항상 양 끝단만 추가로 확인하고, 그 내부는 캐싱해둔 결과를 이용함.

	이는 펠린드롬 문자열의 특성 상, 펠린드롬 문자열의 양 끝에 동일한 문자를 추가하면 
	그대로 새로운 펠린드롬을 얻을 수 있기 때문임.
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