
#include <iostream>
#include <memory.h>
#include <vector>

constexpr int MAX = 1000001;
bool is_prime[MAX];
std::vector<int> prime;

inline void change_bool(int strt, int acc, bool flag);
void eratosthenes();

bool is_under_prime(int num)
{
    int count = 0;
    if (is_prime[num])
        return false;
    for (const int& p : prime)
    {
        while ((num % p) == 0)
        {
            num /= p;
            count++;
        }
    }
    return is_prime[count];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    eratosthenes();
    for (int i = 2; i <= 1000000; ++i)
    {
        if (is_prime[i])
            prime.push_back(i);
    }

    int start, end, result = 0; // both included
    std::cin >> start >> end;
    for (int i = start; i <= end; ++i)
    {
        if (is_under_prime(i))
            result++;
    }
    std::cout << result;
}

// ���� �������� Ư�� �Ҹ������� �ٲٴ� �ζ��� �Լ�
inline void change_bool(int strt, int acc, bool flag)
{
    for(int i = strt; i < MAX; i += acc){
        is_prime[i] = flag;
    }
}

void eratosthenes()
{
    memset(is_prime, 0, sizeof(is_prime));
    is_prime[2] = true;//2�� �Ҽ���.
    is_prime[3] = true;//3�� �Ҽ���. �̷��� 5 �̻��� Ȧ���� �Ǻ��ϸ� �ȴ�.
    // 5 (mod 6) �� 1 (mod 6)�� ������ �����Ѵ�. �̵��� 2�ǹ���� �ƴϰ� 3�� ����� �ƴ� ���������̴�.
    // ��, 1�� �Ҽ��� �ƴϱ⿡ 1 (mod 6)�� 7���� �����Ѵ�.
    change_bool(5, 6, true);
    change_bool(7, 6, true);

    for (int i = 5, j = 25; j < MAX;){
        int nxt = (i - 3) % 6; // ������ i�� 5 (mod 6) �̸� 2, 1 (mod 6) �̸� 4�� �ȴ�.
        if (is_prime[i] == true){
            int addi = i * 6; //i�� 6��� �Ͽ� x (mod 6)�� ���� �˻��ϰ� �Ѵ�.

            // i * i �̻��� ���� ����������. ������ �� �̸��� ������ �̹� �Ҽ� ���ΰ� �Ǻ��Ǿ���.
            change_bool(j, addi, false);
            
            //���� �������� ������ �κ��� ���� ����������.
            change_bool(nxt * i + j, addi, false); // nxt * i + j == i * ( i + nxt)
        }
        // ���� ���� ������ ���� �غ�. ������ i�� 5 (mod 6) �̸� 2��, 1 (mod 6) �̸� 4�� ���Ѵ�.
        i += nxt;
        j = i * i;
    }
}
