
/*
	매나커 알고리즘.

	https://ialy1595.github.io/post/manacher/

	주어진 문자열 안에서 펠린트롬 문자열을 찾아내는 최고의 알고리즘.
	시간 복잡도는 O(N)

	시간 복잡도가 O(N)인 이유는 아래 알고리즘에서 rEnd가 확장하는 과정과 관련됨.
	rEnd는 무조건 O(N)만큼만 확장이 가능함.
		rEnd가 확장하는 경우는
			탐색 과정의 현 중심값이 기존의 rEnd를 넘어선 경우
	rEnd가 확장하지 않는 경우 또한 모두 합치면 O(N)임.

	rEnd의 확장, 비 확장 경우의 수가 각 O(N)이라서 합치면 O(2 * N)임.
*/

#include <string>
#include <vector>

int getPelindromeNum(const std::string &s)
{
	std::string str;
	int centerPos, rEnd, lEnd;

	// 펠린드롬 문자열을 구하는 과정에서 짝수 펠린드롬과 펠린드롬의 길이를 구하기 위해서
	// 기존 문자열을 구성하는 문자 앞뒤로 임의의 문자를 추가한다.
	for (int i = 0; i < s.size(); ++i)
	{
		str.push_back(' ');
		str.push_back(s[i]);
	}
	str.push_back(' ');
	std::vector<int> lenPelinCenter(str.size(), 0);

	// 이하는 매나커 알고리즘, 매나커 알고리즘은 해당 위치를 중간으로 하는 펠린드롬 문자열의 한 쪽 길이를 저장함.
	rEnd = -1, centerPos = -1;
	for (int curPos = 0; curPos < str.size(); ++curPos)
	{
		if (curPos > rEnd) // 기존에 구한 pelindrome 정보 재활용 불가능함.
		{
			// 새로 구한다.
			centerPos = rEnd = curPos;

			// inrange 하고, 좌우가 대칭하다면(l == r) pelindorme하다. 즉 rEnd를 오른 쪽으로 확장함.
			// rEnd < 2 * centerPos => 0 <= lEnd
			while (rEnd < str.size() && rEnd < 2 * centerPos && str[rEnd] == str[2 * centerPos - rEnd])
				rEnd++;
			rEnd--;
			lenPelinCenter[curPos] = rEnd - centerPos;
		}
		else // 기존에 구한 pelindrome의 일부분인 경우, 앞서 구한 정보를 재활용한다.
		{
			int oppositePos = 2 * centerPos - curPos;
			// using lCurPos's value, get curPos's value
			if (lenPelinCenter[oppositePos] < rEnd - curPos)
			{
				// 반대편lcurPos의 rad가 기존 중심을 넘지 않음. 오직 일부로만 존재함
				// 대칭성에 의해서 반대편의 내용이 그대로 반영됨.
				lenPelinCenter[curPos] = lenPelinCenter[oppositePos];
			}
			else if (lenPelinCenter[oppositePos] > rEnd - curPos)
			{
				lenPelinCenter[curPos] = rEnd - curPos;
			}
			else // rEnd의 확장, 모든 경우를 다 합치면 O(N)임.
			{
				centerPos = curPos;

				while (rEnd < str.size() && rEnd < 2 * centerPos && str[rEnd] == str[2 * centerPos - rEnd])
					rEnd++;
				rEnd--;
				lenPelinCenter[curPos] = rEnd - centerPos;
			}
		}
	}
	//
	int cnt = 0;
	for (int n : lenPelinCenter)
	{
		if (n > 0)
			cnt += (n >> 1) + 1;
	}
	return cnt;
}
