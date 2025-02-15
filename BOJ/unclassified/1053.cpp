// 4���� �������� �־��� ���ڿ��� �縰������� ������
// 1. insert
// 2. erase
// 3. swap
// 4. exchange, 1���� ��� ������.
// DP�� �����ΰ�... �޸𸮿� ��δ� ���� �̿��ؼ� �ߺ� ������ ������. 
// �׷��ٸ�, ��� �ߺ��� �Ǵ�����?
// ���ʿ� ��� ���¸� ��������?
// ���ڿ��� ���¸� �����ϴ� �� -> map?
// ���¶�� ���� ������ ���� ���̴�. ��� ���̸� Ȯ������? 

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
