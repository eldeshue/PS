
#include <iostream>
#include <bitset>

using Bits64 = std::bitset<64>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// in the bitset, LSB goes to index 0
	unsigned long long targetNum;
	std::cin >> targetNum;
	Bits64 nSmall = targetNum, nBig = targetNum;
	// find nearest small
	// find onebit after zero bit
	// swap and pull
	int oneCnt = 0;
	for (int i = 0; i < 63; ++i)
	{
		if (nSmall[i] == 0 && nSmall[i + 1] == 1)
		{
			nSmall[i] = 1;
			nSmall[i + 1] = 0;
			//
			if (i > 0 && oneCnt > 0)
				nSmall = (nSmall.to_ullong() | ((1ULL << i) - 1)) & ~((1ULL << oneCnt) - 1);
			break;
		}
		else if (nSmall[i] == 0)
		{
			oneCnt++;
		}
	}
	if (nSmall.to_ullong() == targetNum)
	{
		nSmall = 0ULL;
	}
	// find nearest big
	// find zero bit after one bit
	// swap and pull the whole
	oneCnt = 0;
	for (int i = 0; i < 63; ++i)
	{
		if (nBig[i] == 1 && nBig[i + 1] == 0)
		{
			// swap
			nBig[i] = 0;
			nBig[i + 1] = 1;
			if (i > 0 && oneCnt > 0)
				nBig = (nBig.to_ullong() & ~((1ULL << i) - 1)) | ((1ULL << oneCnt) - 1);
			break;
		}
		else if (nBig[i] == 1)
		{
			oneCnt++;
		}
	}
	std::cout << nSmall.to_ullong() << ' ' << nBig.to_ullong();
}
