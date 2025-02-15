
#include <iostream>

using namespace std;

// solution class
/*
    xor을 응용한 dp문제.

    문제의 상황은 wonderful substring의 개수를 찾아내는 것.
    wonderful substring은 substring이므로 연속되어야 하며,
    wonderful하기 위해서는 해당 substring을 구성하는 알파뱃이 
        하나가 홀수거나 모두 짝수여야 함.

    이러한 string의 상태는 bit mask로 구현이 가능함.
    해당 string에서 홀수인 알파뱃을 1, 짝수인 알파뱃을 0이라 함.
    그러면 xor 연산을 통해서 substring의 결합을 O(1)에 처리할 수 있음.

    상태가 표현되었으니, 크게 두 가지 solution이 존재함.
    sol 1) 단순한 DP, O(N ^ 2)
    상태공간의 caching을 통한 심플한 dp임.
    prev status와 그 개수를 이용, cur status와 그 개수를 count함.

    sol 2) 누적합을 이용한 DP, O(N)
    xor연산은 결합성 뿐만 아니라 역원이 존재함. 심지어 역원이 자기 자신임.
    (자기 자신과의 xor은 항상 0임)

    이러한 역원의 성질을 활용하여 상태를 복원하기 위해서 상태를 누적 갱신해가며
    각 누적된 상태에 대해서 wonderful substring을 복원하는 역원을 찾아서 그 개수를 샌다.

*/

/*
#include <array>

class Solution {
public:
    long long wonderfulSubstrings(string word)
	{
        array<long long, 1024> cache;
        int status = 0;
        long long result = 0;

        fill(cache.begin(), cache.end(), 0);
        for (const char& c : word)
        {
            status ^= 1 << (c - 'a');   // 누적 합 갱신
            // 역원을 활용한 복원, 즉 xor시 wonderful해지는 수를 count
            result += cache[status];
            for (int i = 0; i < 10; ++i)
            {
                result += cache[status ^ (1 << i)]; 
            }
            // 누적 합 가지수 업데이트
            cache[status]++;
        }
        // 최종 상태의 wonderful substring
        result += cache[0];
        for (int i = 0; i < 10; ++i)
        {
            result += cache[1 << i];
        }
        return result;
    }
};
// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
    std::cout << test.wonderfulSubstrings("aba");
}
 */