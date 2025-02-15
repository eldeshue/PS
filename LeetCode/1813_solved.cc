

#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <sstream>
class Solution
{
private:
	vector<string> sentenceToWords(const string &str)
	{
		vector<string> result;
		istringstream ss(str);
		string temp;

		while (ss >> temp)
			result.push_back(temp);
		return result;
	}

	int getPrefixLen(auto const begin1, auto const end1, auto const begin2, auto const end2)
	{
		int result = 0;
		auto itr1 = begin1;
		auto itr2 = begin2;

		while (itr1 != end1 && itr2 != end2 && *itr1 == *itr2)
		{
			result++;
			itr1++;
			itr2++;
		}
		return result;
	}

public:
	// solution method
	bool areSentencesSimilar(string sentence1, string sentence2)
	{
		if (sentence1.empty() || sentence2.empty() || sentence1 == sentence2)
			return true;
		vector<string> const words1 = sentenceToWords(sentence1);
		vector<string> const words2 = sentenceToWords(sentence2);

		// word 단위로 일치 여부 판단해야 함.
		// s2에 하나를 삽입해서 s1이 되어야 함.
		// 따라서 s1에서 s2는 발견되어야 함.
		// prefix, suffix 찾아내야 함.
		// split해서 string vector에 몰아넣고, 비교를 수행.
		// 같거나 크다로 비교를 해야 하는 이유 : A B CC DD B B, A B B -> prefix = 2, suffix = 2
		// prefix = wordsLen 혹은 suffix = wordsLen인 경우를 위해서도 같거나 크다로 비교해줘야 함.
		const int prefixLen = getPrefixLen(words1.begin(), words1.end(), words2.begin(), words2.end());
		const int suffixLen = getPrefixLen(words1.rbegin(), words1.rend(), words2.rbegin(), words2.rend());
		const int sumLen = prefixLen + suffixLen;
		return sumLen >= words1.size() || sumLen >= words2.size();
	}
};
auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
