
#include <iostream>
#include <string>

using namespace std;

// solution class
#include <map>
class Solution
{
private:
	string_view parseAtom(string_view sv, int &pos)	// parse Atoms
	{
		int start = pos;
		pos++;
		while (pos < sv.size() && isalpha(sv[pos]) && !isupper(sv[pos]))
		{
			pos++;
		}
		return string_view(sv.begin() + start, sv.begin() + pos);
	}
	int parseNum(string_view sv, int &pos)	// parse coefficient
	{
		int val = atoi(sv.data() + pos);
		while (pos <sv.size() && '0' <= sv[pos] && sv[pos] <= '9')
			pos++;
		if (val == 0)
			val = 1;
		return val;
	}
	void countSegAtoms(string_view sv, map<string_view, int> &freq, int coeff)
	{
		bool isAtom = false;
		int pos = 0;
		while (pos < sv.size())
		{
			int  coef = 1;
			if (sv[pos] == '(')	// recursive count
			{
				// parse expression
				pos++;
				int end = pos;
				int nestCount = 1;
				while (true)	// balance parenthesis
				{
					if (nestCount == 1 && sv[end] == ')')
					{
						break;
					}
					else if (sv[end] == ')')
					{
						nestCount--;
					}
					else if (sv[end] == '(')
					{
						nestCount++;
					}
					end++;
				}
				// get number
				int nextPos = end + 1;
				coef = parseNum(sv, nextPos);
				countSegAtoms(string_view(sv.begin() + pos, sv.begin() + end),
					freq, coeff * coef);
				pos = nextPos;
			}
			else	// simple count
			{
				// get Atom
				string_view atom = parseAtom(sv, pos);
				// get number
				int coef = parseNum(sv, pos);
				// update
				freq[atom] += coef * coeff;
			}
		}
	}

public:
	// solution method
	string countOfAtoms(string fomula)
	{
		string result;
		map<string_view, int> freq;
		countSegAtoms(fomula, freq, 1);	// count atoms
		for (const auto &entry : freq)	// set result
		{
			result.append(entry.first);
			if (entry.second != 1)
				result.append(to_string(entry.second));
		}
		return result;
	}
	//
};

// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
	std::cout << test.countOfAtoms("K4(ON(SO3)2)2");
}