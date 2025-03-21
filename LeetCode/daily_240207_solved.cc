
#include <iostream>
#include <string>

using namespace std;

// solution
#include <algorithm>
#include <memory.h>

int freqTable[52];
void setFreq(char c)
{
	if (48 <= c && c <= 57)
		freqTable[c - 48]++;
	else if (65 <= c && c <= 90)
		freqTable[c - 65 + 10]++;
	else if (97 <= c && c <= 122)
		freqTable[c - 97 + 36]++;
}

int getFreq(char c)
{
	if (48 <= c && c <= 57)
		return freqTable[c - 48];
	else if (65 <= c && c <= 90)
		return freqTable[c - 65 + 10];
	else if (97 <= c && c <= 122)
		return freqTable[c - 97 + 36];
	return 0;
}

void setFreqTable(const string& str)
{
	memset(freqTable, 0, sizeof(freqTable));
	for (const char c : str)
		setFreq(c);
}

bool compareByFreq(const char& c1, const char& c2)
{
	// decreasing order
	int freq1 = getFreq(c1);
	int freq2 = getFreq(c2);
	if (freq1 == freq2)
		return c1 > c2;
	return freq1 > freq2;
}

class Solution
{
public:
	string frequencySort(string s)
	{
		setFreqTable(s);
		sort(s.begin(), s.end(), compareByFreq);
		return s;
	}
};

// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
	string str1 = "tree";
	string str2 = "cccaaa";
	string str3 = "1a1A1abbb344444444444";
	std::cout << test.frequencySort(str1) << '\n';
	std::cout << test.frequencySort(str2) << '\n';
	std::cout << test.frequencySort(str3) << '\n';
}
