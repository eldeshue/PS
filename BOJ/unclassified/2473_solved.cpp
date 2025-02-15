
#include <iostream>
#include <algorithm>

long long minAbsVal = 3e9;
int iL, iM, iR, N;
int buffer[5000];

void SearchMidRight(int icurL)	// two pointer algorithm
{
	int icurM = icurL + 1, icurR = N - 1;
	while (icurM != icurR)
	{
		long long newAbsVal = buffer[icurL] + static_cast<long long>( buffer[icurM] + buffer[icurR]);
		if (std::abs(newAbsVal) <= std::abs(minAbsVal))
		{
			minAbsVal = newAbsVal;
			iL = icurL;
			iM = icurM;
			iR = icurR;
		}

		if (newAbsVal >= 0)
		{
			icurR--;
		}
		else
		{
			icurM++;
		}
	}
}

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
	std::sort(buffer, buffer + N);

	for (int start = 0; start < N - 2; ++start)
	{
		SearchMidRight(start);
	}
	
	std::cout << buffer[iL] << " " << buffer[iM] << " " << buffer[iR];
}