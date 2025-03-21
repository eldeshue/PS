

/*

// solution
class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> result;
        int seqDigits[] = {12, 23, 34, 45, 56, 67, 78, 89,
            123, 234, 345, 456, 567, 678, 789, 1234, 2345, 3456, 4567,
            5678, 6789, 12345, 23456, 34567, 45678, 56789,
            123456, 234567, 345678, 456789, 1234567, 2345678, 3456789,
            12345678, 23456789, 123456789};

        for (int i = 0; i < 36; ++i)
        {
            const int& num = seqDigits[i];
            if (low <= num && num <= high)
                result.push_back(num);
        }
        return result;
    }
};

// to get solution, generate sequential numbers.
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> result;

	for (int len = 2; len < 10; ++len)
	{
		for (int start = 1; start <= 10 - len; ++start)
		{
			int num = 0;
			int digit = start;
			for (int base = pow(10, len - 1); base >= 1; base /= 10)
				num += base * digit++;
			result.push_back(num);
		}
	}

	for (const int& num : result)
		std::cout << num << ", ";
}

*/
