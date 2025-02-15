
/*
	이상한 프린터

	프린터로 주어진 문자열을 생성한다. 생성하는데 몇 번의 작업을 수행해야 하는가?

	프린터는 다음의 원칙을 갖는다.
	1. 프린터는 한 번에 하나의 문자로 구성된, 연속된 문자열을 생성할 수 있다.
	2. 프린터는 기존 문자열의 앞, 뒤, 그리고 덮어쓰기도 할 수 있다.

	주어진 문자열 s는 길이가 최대 100, 소문자 알파뱃으로 구성된다.

	---------------------------------------------------------------------

	lower bound : s에 등장하는 문자의 종류, 즉 최대 26이다.
		ex) 문자별로 한 번 씩만 찍는 경우
		aaaaaaabbbbbbcccccbbbbbbaaaa -> 3
	upper bound : 문자열의 길이, 즉 최대 100이다. 한 번에 한 글자씩 찍으면 된다.

	그렇다면, 어떤 경우에 한 종류의 문자를 두 번 이상 찍어야 할까?
		ex) aaaabbbaaabbbaaa -> b나 a, 둘 중 하나를 두 번 찍어야 한다. 총 3회
		ex) aaaabbbbbaaaaabbbb -> 위와 마찬가지, 총 3회

	가장 쉬운 풀이는 상태공간 탐색. 상태공간 탐색을 dp로 최적화 하자.
	상태 : 문자열, 횟수 -> cache로 해시맵 사용?

*/
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")

class Solution
{
private:
public:
	// solution method
	int strangePrinter(string s)
	{
	}
};
auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
