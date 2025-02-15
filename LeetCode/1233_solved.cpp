
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <algorithm>
#include <unordered_map>
class Solution
{
private:
	using TrieNode = unordered_map<string_view, int>;
	using Trie = std::vector<TrieNode>;
public:
	// solution method
	vector<string> removeSubfolders(vector<string>& folder)
	{
		vector<string> result;
		// sort
		std::sort(folder.begin(), folder.end());
		// build trie
		Trie trie(1);
		for (const string &path : folder)
		{
			bool isSub = false;
			int curPos = 0;
			int start = 0, end = 1;
			for (; end <= path.size(); ++end)
			{
				if (end == path.size() || path[end] == '/')
				{
					// sub dir identified
					string_view curDir(path.begin() + start, path.begin() + end);
					if (trie[curPos].find(curDir) == trie[curPos].end())
					{
						// subdir detect
						if (trie[curPos].find(".") != trie[curPos].end())
						{
							isSub = true;
							break;
						}
						// add new node
						trie[curPos].insert(make_pair(curDir, trie.size()));
						trie.push_back(TrieNode());
					}
					curPos = trie[curPos][curDir];
					start = end;
				}
			}
			if (!isSub)
			{
				trie[curPos].insert(make_pair(".", -1));
				result.push_back(path);
			}
		}
		// return
		return result;
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

