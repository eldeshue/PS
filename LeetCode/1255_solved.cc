
#include <iostream>
#include <vector>

using namespace std;

// solution
#include <string>
#include <map>

class Solution
{
private:
	map<string, int> cache;
	string maxStat;
	int wordCnt;

	inline bool isStatusOk(const string &s)
	{
		for (int i = 0; i < 26; ++i)
		{
			if (maxStat[i] < s[i])
			{
				return false;
			}
		}
		return true;
	}
	inline string combineStatus(const string &s1, const string &s2)
	{
		string result;

		result.resize(26);
		for (int i = 0; i < 26; ++i)
		{
			result[i] = s1[i] + s2[i];
		}
		return result;
	}

public:
	// solution method
	int maxScoreWords(vector<string> &words,
					  vector<char> &letters,
					  vector<int> &score)
	{
		// preprocess string
		wordCnt = words.size();
		vector<pair<string, int>> wordStat;
		for (const string &word : words)
		{
			wordStat.push_back(make_pair(string(26, '\0'), 0));
			for (const char &c : word)
			{
				wordStat.back().first[c - 'a']++;
				wordStat.back().second += score[c - 'a'];
			}
		}

		// max status setting
		maxStat.resize(26);
		fill(maxStat.begin(), maxStat.end(), 0);
		for (const char &c : letters)
		{
			maxStat[c - 'a']++;
		}

		// dp, tabulation
		int result = 0;
		cache.insert(make_pair(string(26, '\0'), 0));
		for (int i = 0; i < wordCnt; ++i)
		{
			for (auto itr = cache.rbegin(); itr != cache.rend(); itr++)
			{
				pair<const string, int> &entry = *itr;
				string nextStat = combineStatus(entry.first, wordStat[i].first);
				if (cache.find(nextStat) == cache.end() && isStatusOk(nextStat))
				{
					cache[nextStat] = entry.second + wordStat[i].second;
					result = max(result, cache[nextStat]);
				}
			}
		}
		return result;
	}
};
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
