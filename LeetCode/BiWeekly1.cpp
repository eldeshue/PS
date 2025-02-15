
#include <iostream>
#include <vector>

#include <string>

using namespace std;

// solution class

/*
class Solution
{
public:
	// solution method

	//
};
*/

// 100221, easy
/*
class Solution
{
public:
	// solution method
	int maxOperations(vector<int>& nums)
	{
		int result = 0, val = nums[0] + nums[1];
		for (int i = 0; i < nums.size() / 2; ++i)
		{
			if ((nums[2 * i] + nums[2 * i + 1]) == val)
				result++;
			else
				break;
		}
		return result;
	}
	//
};
// solution class
*/

// 100211 
/*
#include <memory.h>

class Solution
{
private:
	int alphaCnt[26];
public:
	// solution method
	string lastNonEmptyString(string s)
	{
		string result;
		vector<int> eraseCnt(s.size(), 0);
		int key, lastCnt = 0;

		memset(alphaCnt, 0, sizeof(alphaCnt));
		for (int i = 0; i < s.size(); ++i)
		{
			if (isalpha(s[i]))
			{
				key = s[i] - 'a';
				alphaCnt[key]++;
				eraseCnt[i] = alphaCnt[key];
				lastCnt = std::max(lastCnt, alphaCnt[key]);
			}
		}
		for (int i = 0; i < s.size(); ++i)
		{
			if (eraseCnt[i] == lastCnt)
			{
				result.push_back(s[i]);
			}
		}
		return result;
	}
	//
};
*/
// failed 3040
#include <queue>
#include <memory.h>

class Solution
{
private:
	int cache[2000][2000];	// visited
	int maxOps;
public:
	Solution()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
		memset(cache, 0, sizeof(cache));
		maxOps = 0;
	}
	// solution method
	int maxOperations(vector<int>& nums)
	{

	}
	//
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}