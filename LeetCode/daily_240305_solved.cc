
/*
	문자열 조작

	a, b, c의 세 문자로만 이루어진 문자열이 주어진다.
	1. 접두어를 정한다. 접두어는 모두 같은 문자로 이루어져야 함.
	2. 접미어를 정한다. 접미어는 모두 같은 문자로 이루어져야 함.
	3. 접두어와 접미어는 겹쳐서는 안된다.
	4. 접두어와 접미어를 이루는 문자는 같아야 한다. 즉 같은 문자가 앞뒤로 구성되어야 함.
	5. 접두어와 접미어를 모두 지운다.

	위 조작을 필요한 만큼 반복하여 가능한 짧은 길이를 남길 수 있도록 한다.

	투 포인터를 응용하여 좌우의 끝에서 시작하여 가능한 만큼 지울 수 있도록 한다.
*/
#include <iostream>
#include <string>

using namespace std;

// solution
#pragma GCC optimize("03")
#pragma GCC target ("avx")

class Solution
{
public:
	int minimumLength(string s)
	{
		// [left, right]
		int left = 0, right = s.size() - 1;

		while (left <= right && s[left] == s[right])
		{
			const char val = s[left];
			if (left == right)
				break;
			while (s[left] == val && s[right] == val && left < right)
			{
				left++;
				right--;
			}
			while (s[left] == val && left <= right)	// move left pointer
			{
				left++;
			}
			while (s[right] == val && left <= right)	// move right pointer
			{
				right--;
			}
		}
		return right - left + 1;
	}
};

// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
	//string str = "cccccccccccccccccccccccccccccccccccccccccccccccccccccccccbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbcccccccbcaabccbacaabcbaccaacccaabbcaabbbbcaccbbcbbbbbabcacbccbaaaccaaaabcacbccbbcaabccacbccbbcaaaccaaccbbcaabaabbcaccaabbcbaacbaccbaaabccbaabcacbabcabbccbacaabbcaacaaacaaacbabbcabccbbacaabacabcacacbcacaabbabcbaaaccccacbbabcbccbaaccbbbabbbbaabcccaabaacccccccbbabcbcbcbcbcbbbbccbbaaccaaaaccacabbaccbbabccaacbcbccaabcacacacaaabbbaaccccaccaabcabbabacacbbaacbcabbbcaccccacccbcaccccccccbbcccbbaabbcbcaabcccbabcbcbccacaccbcaacbaaaaaababbaaccbcccaccccababcccacbccbbacabcbbbccbcababbaaaacaabccbaaacbacbcaababbcbacccacaccbabcabbccaccacbccaaccabbabcbbccaabccaacabbaabccacbabcaababccbcaacababbabcacccaaabcaabcbbbbabcbccbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbcccccccccc";
	//string str = "abbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbba";
	string str = "bbbbbbbbbbbbbbbbbbbbbbbbbbbabbbbbbbbbbbbbbbccbcbcbccbbabbb";
	cout << test.minimumLength(str);
}
