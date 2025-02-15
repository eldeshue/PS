

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// solution class
#include <bitset>
#include <unordered_set>

class Solution
{
private:
	unordered_set<string_view> words;
	void backTrack(vector<string>& result, const string_view& str,
		bitset<20> stat, int startIdx)
	{
		for (int i = startIdx; i < str.size(); ++i)
		{
			if (words.find(str.substr(startIdx, i + 1 - startIdx))
					!= words.end())
			{
				stat[i] = true;
				backTrack(result, str, stat, i + 1);
				stat[i] = false;
			}
		}
		if (words.find(str.substr(startIdx, str.size() + 1 - startIdx))
				!= words.end())
		{
			result.push_back(string());
			for (int i = 0; i < str.size(); ++i)
			{
				result.back().push_back(str[i]);
				if (stat[i])
					result.back().push_back(' ');
			}
		}
		return;
	}

public:
	vector<string> wordBreak(string s, vector<string>& wordDict)
	{
		vector<string> result;

		for (const string &str : wordDict)
		{
			words.insert(str);
		}
		backTrack(result, s, 0, 0);
		return result;
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

