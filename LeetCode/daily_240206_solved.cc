
/*
	애너그램 분할

	주어진 문자열의 집합에서 애너그램인 문자열들을 묶는다.

	문자열들의 개수, N : 10000
	문자열의 최대 길이, M : 100

	solution 1)
	문자열을 정렬하고, 정렬한 문자열에 key값을 할당하여 매칭시킴.
	즉 정렬 알고리즘을 hash함수로 삼아서 분류하기

	solution 2)
    정렬 대신 보다 싼 hash function을 도입하여 문제를 해결.
    특히 문자의 등장 순서에 상관 없는 알고리즘을 도입한다.

	10000 * 100 * log(100)
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// solution
#include <unordered_map>

using ull = unsigned long long;

class Solution
{
private:
	// * important *
	// get hash value of anagram from string, using prime numbers.
	ull getHashAnagram(const string& str) const
	{
		// input string is always a combination of lower alphabet
		constexpr ull	primeTable[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
										43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
		constexpr ull	primeModulus = (1ULL << 58) - 27;
		ull				hashValue = 1;

		for (const char& c : str)	// O(M)
			hashValue = (hashValue * primeTable[c - 'a']) % primeModulus;
		return hashValue;
	}	// O(M)

public:
	vector<vector<string>> groupAnagrams(vector<string>& strs)
	{
		vector<vector<string>>	result;
		unordered_map<ull, int>	anagramIdxHashMap;
		int						lastIdx = 0;
		ull						hash;
		int						idx;

		for (const string& str : strs)	// O(N)
		{
			hash = getHashAnagram(str);
			if (anagramIdxHashMap.find(hash) == anagramIdxHashMap.end())
			{
				// add new entry.
				anagramIdxHashMap.insert(make_pair(hash, lastIdx));
				// add vector of string
				result.push_back(vector<string>());
				// add string
				result[lastIdx++].push_back(str);
			}
			else
			{
				idx = anagramIdxHashMap[hash];
				result[idx].push_back(str);
			}
		}	// total : O(M * N)
		return result;
	}

};

// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	//vector<string> input = {"eat","tea","tan","ate","nat","bat"};
	vector<string> input = {"a"};
	Solution test;
	vector<vector<string>> result = test.groupAnagrams(input);
	for (const vector<string>& strs : result)
	{
		for (const string& str : strs)
		{
			cout << str << ' ';
		}
		cout << '\n';
	}
}
