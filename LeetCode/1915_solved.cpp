
#include <iostream>

using namespace std;

// solution class
/*
    xor�� ������ dp����.

    ������ ��Ȳ�� wonderful substring�� ������ ã�Ƴ��� ��.
    wonderful substring�� substring�̹Ƿ� ���ӵǾ�� �ϸ�,
    wonderful�ϱ� ���ؼ��� �ش� substring�� �����ϴ� ���Ĺ��� 
        �ϳ��� Ȧ���ų� ��� ¦������ ��.

    �̷��� string�� ���´� bit mask�� ������ ������.
    �ش� string���� Ȧ���� ���Ĺ��� 1, ¦���� ���Ĺ��� 0�̶� ��.
    �׷��� xor ������ ���ؼ� substring�� ������ O(1)�� ó���� �� ����.

    ���°� ǥ���Ǿ�����, ũ�� �� ���� solution�� ������.
    sol 1) �ܼ��� DP, O(N ^ 2)
    ���°����� caching�� ���� ������ dp��.
    prev status�� �� ������ �̿�, cur status�� �� ������ count��.

    sol 2) �������� �̿��� DP, O(N)
    xor������ ���ռ� �Ӹ� �ƴ϶� ������ ������. ������ ������ �ڱ� �ڽ���.
    (�ڱ� �ڽŰ��� xor�� �׻� 0��)

    �̷��� ������ ������ Ȱ���Ͽ� ���¸� �����ϱ� ���ؼ� ���¸� ���� �����ذ���
    �� ������ ���¿� ���ؼ� wonderful substring�� �����ϴ� ������ ã�Ƽ� �� ������ ����.

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
            status ^= 1 << (c - 'a');   // ���� �� ����
            // ������ Ȱ���� ����, �� xor�� wonderful������ ���� count
            result += cache[status];
            for (int i = 0; i < 10; ++i)
            {
                result += cache[status ^ (1 << i)]; 
            }
            // ���� �� ������ ������Ʈ
            cache[status]++;
        }
        // ���� ������ wonderful substring
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