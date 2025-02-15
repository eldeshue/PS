
#include <iostream>

using namespace std;

// solution class
/*
    A�� ���� 2�� �̸��̾�� �� -> A�� ���� ����� ���� ���ϰ�
        m�� �� �ϳ��� ���� ������ ��.

    L�� 3�� �������� ������ �ȵ� -> dp�� Ȱ���Ͽ� ������ �ڵ�

    n : length of record
    m : number of A and P, so number of L is n - m

    f(n, m) : ���̰� n�̰� ������ ���ڵ尡 A Ȥ�� P
                A�� P�� ���ļ� m��
    g(n, m) : ���̰� n�̰� ������ ���ڵ常 L
                A�� P�� ���ļ� m��
    h(n, m) : ���̰� n�̰� ������ �� ���ڵ常 L
    ��ȭ��
    g(n, m) = f(n - 1, m)
    h(n, m) = f(n - 2, m)
    f(n, m) = f(n - 1, m - 1) + g(n - 1, m - 1) + h(n - 1, m - 1)
            = f(n - 1, m - 1) + f(n - 2, m - 1) + f(n - 3, m - 1)

*/
using ll = int;
constexpr ll DIV = 1000000007;
#include <vector>

class Solution
{
private:
public:
	// solution method
    int checkRecord(int n)
    {
        if (n == 1)
            return 3;
        vector<vector<ll>> cacheF(n + 1, vector<ll>(n + 1, -1));
        vector<vector<ll>> cacheG(n + 1, vector<ll>(n + 1, -1));
        vector<vector<ll>> cacheH(n + 1, vector<ll>(n + 1, -1));

        // set initial value at cache
        // cache[N][M]
        cacheF[1][1] = 1;
        cacheF[2][1] = 1; cacheF[2][2] = 1;

        cacheG[1][0] = 1; 
        cacheG[2][0] = 0; cacheG[2][1] = 1;

        cacheH[2][0] = 1;
        for (int len = 3; len <= n; ++len)
        {
            for (int m = 1; m <= len; ++m)
            {
                cacheF[len][m] = (cacheF[len - 1][len - 1] + cacheG[len - 1][m - 1] + cacheH[len - 1][m - 1]) % DIV;
                cacheG[len][m] = cacheF[len - 1][m - 1];
                cacheH[len][m] = cacheF[len - 2][m - 1];
            }
        }
        ll result = 0;
        for (int m = 0; m <= n; ++m)
        {
            if (cacheF[n][m] != -1)
                result = (result + cacheF[n][m] * (m + 1)) % DIV;
            if (cacheG[n][m] != -1)
                result = (result + cacheG[n][m] * (m + 1)) % DIV;
            if (cacheH[n][m] != -1)
                result = (result + cacheH[n][m] * (m + 1)) % DIV;
        }
        return result;
    }

	//
};

// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
    std::cout << test.checkRecord(2) << '\n';
    std::cout << test.checkRecord(1) << '\n';
    std::cout << test.checkRecord(10101) << '\n';
}
