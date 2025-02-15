
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// solution
#include <unordered_map>
class Solution
{
private:
	using TrieNode = unordered_map<char, int>;
	using Trie = vector<TrieNode>;
	Trie t;
	void buildTrie(const std::string &str)
	{
		int curNode = 0;

		if (t.empty())
			t.push_back(TrieNode());
		for (int idx = 0; idx < str.size(); ++idx)
		{
			if (idx == str.size() - 1)
			{
				// mark end
				t[curNode][str[idx]] = -1;
				break;
			}
			else if (t[curNode].find(str[idx]) == t[curNode].end())
			{
				t[curNode][str[idx]] = t.size();
				t.push_back(TrieNode());
			}
			curNode = t[curNode][str[idx]];
			if (curNode == -1)
				return;
		}
	}
	int getRootLen(string_view derived)
	{
		int curNode = 0, result = 0;

		// append target
		for (int idx = 0; idx < derived.size(); ++idx)
		{
			if (t[curNode].find(derived[idx]) != t[curNode].end())
			{
				curNode = t[curNode][derived[idx]];
				result++;
				if (curNode == -1)
				{
					break;
				}
			}
			else
			{
				return 0;
			}
		}
		return result;
	}

public:
	// solution method, use trie
	string replaceWords(vector<string> &dictionary, string sentence)
	{
		string result;
		// build trie, mark end
		for (const string &word : dictionary)
		{
			buildTrie(word);
		}
		// two pointer with state machine
		bool spaceFlag = true;
		int fast = 0, slow = 0;
		while (fast <= sentence.size())
		{
			if (!spaceFlag && (fast == sentence.size() || isspace(sentence[fast])))
			{
				// search, replace
				// from slow to fast - 1, both included
				int rootLen = getRootLen(string_view(sentence).substr(slow, fast - slow));
				if (rootLen == 0)
					rootLen = fast - slow;
				result.append(sentence.begin() + slow, sentence.begin() + slow + rootLen);
				spaceFlag = true;
				if (isspace(sentence[fast]))
					result.push_back(sentence[fast]);
			}
			else if (spaceFlag && !isspace(sentence[fast]))
			{
				slow = fast;
				spaceFlag = false;
			}
			else if (spaceFlag) // add space
			{
				result.push_back(sentence[fast]);
			}
			fast++;
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
