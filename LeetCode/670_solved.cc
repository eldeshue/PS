
#include <array>
#include <string>

using namespace std;

class Solution
{
public:
	int maximumSwap(int num)
	{
		array<int, 10> freq;
		fill(freq.begin(), freq.end(), 0);
		string numStr = to_string(num);
		for (const char c : numStr) // counting frequency for bucket sort
			freq[c - '0']++;
		int strIdx = 0;
		for (int n = 9; n >= 0; --n) // compare with the sorted value
		{
			const char sortedChar = n + '0';
			while (freq[n] > 0)
			{
				// find first mismatch, swap needed
				if (numStr[strIdx] != sortedChar)
				{
					// find swap char
					int targetIdx = strIdx + 1;
					for (int i = 0; i < numStr.size(); ++i)
					{
						if (sortedChar == numStr[i])
							targetIdx = i; // pick farest one
					}
					// swap
					swap(numStr[strIdx], numStr[targetIdx]);
					// return
					return stoi(numStr);
				}
				strIdx++;
				freq[n]--;
			}
		}
		return stoi(numStr);
	}
};
