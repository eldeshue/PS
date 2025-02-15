// 4가지 연산으로 주어진 문자열을 펠린드롬으로 만들어라
// 1. insert
// 2. erase
// 3. swap
// 4. exchange, 1번만 사용 가능함.
// DP란 무엇인가... 메모리에 써두는 것을 이용해서 중복 연산을 제거함. 
// 그렇다면, 어떻게 중복을 판단하지?
// 애초에 어떻게 상태를 정의하지?
// 문자열의 상태를 정의하는 법 -> map?
// 상태라는 것은 구분을 짓는 것이다. 어떻게 차이를 확인하지? 

#include <iostream>
#include <string>
#include <map>

std::string tgtStr;
std::map<std::string, int> cache; // associative memory

bool isPelindrome(const std::string& str)
{
	for (int i = 0; i < str.size() / 2; ++i)
	{
		if (*(str.begin() + i) != *(str.end() -1 - i))
		{
			return false;
		}
	}
	return true;
}

int makePelindrome(std::string str, int count)
{

	if (cache.find(str) == cache.end())
	{
		cache.insert(std::make_pair(str, count));
	}
	else if (cache[str] > count)
	{
		cache[str] = count;
	}
	else
	{
	}

}


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> tgtStr;
}
