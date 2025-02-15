
/*
	kmp algorithm
*/
#ifndef KMP_H
#define KMP_H

#include <string>
#include <vector>

class KMP
{
private:
	std::vector<int> t;
	std::string_view s, w;
	KMP();

public:
	// preprocessing, build partial match table
	KMP(std::string_view heystack, std::string_view needle) : s(heystack), w(needle), t(needle.size() + 1, 0)
	{
		int pos = 1, cnd = 0; // pos : current position of table to fill
		// cnd : next char of current candidate substring

// cnd points at previous position that can be compared.
// cnd also means length of maximum prefix
		t[0] = -1;
		while (pos < w.size())
		{
			if (w[pos] == w[cnd]) // match
			{
				t[pos] = t[cnd];
			}
			else // mismatch
			{
				t[pos] = cnd;
				while (0 <= cnd && w[pos] != w[cnd]) // fall back during mismatch
					cnd = t[cnd];					 // cmd == -1 means no going back
			}
			pos++;
			cnd++;
		}
		t[pos] = cnd; // ???
	}
	// search, positions that "needle" matched int "heystack"
	std::vector<int> operator()()
	{
		std::vector<int> result;
		auto sIdx = 0, wIdx = 0;

		while (sIdx < s.size()) // O( length of s )
		{
			if (s[sIdx] == w[wIdx]) // match
			{
				sIdx++;
				wIdx++;
				if (wIdx == w.size()) // occurence found
				{
					result.push_back(sIdx - wIdx);
					wIdx = t[wIdx]; // not -1
				}
			}
			else // mis match, jump wIdx back
			{
				wIdx = t[wIdx];
				if (wIdx < 0) // -1 means there is no going back
				{
					sIdx++;
					wIdx++;
				}
			}
		}
		return result;
	}
};

#endif
