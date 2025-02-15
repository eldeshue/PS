
#include <iostream>

int minAbsVal = 2e9;
int iL, iR, N;
int buffer[100000];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> buffer[i];
	}

	// two pointer, icurL & icurR
	int icurL = 0, icurR = N - 1;
	while (icurL != icurR)
	{
		int newAbsVal = buffer[icurL] + buffer[icurR];
		if (std::abs(newAbsVal) <= std::abs(minAbsVal))
		{
			minAbsVal = newAbsVal;
			iL = icurL;
			iR = icurR;
		}

		if (newAbsVal >= 0)
		{
			icurR--;
		}
		else
		{
			icurL++;
		}
	}
	std::cout << buffer[iL] << " " << buffer[iR];
}