// �ϳ����� ž.
// �������� ū �� ����.
#include <iostream>
#include <string>
#include <stack>

int N;
std::stack<int> tower[3];

class BigInt // actually, unsigned int
{
private:
	std::string numStr;

public:
	BigInt(int n) { numStr = std::to_string(n); };
	~BigInt() { numStr.clear(); };
	BigInt& operator*(int n);
	BigInt& operator--();

	friend std::ostream& operator<<(std::ostream& o, const BigInt& i);
};

std::ostream& operator<<(std::ostream& o, const BigInt& i) { 
	auto itr = i.numStr.rbegin();
	while (itr != i.numStr.rend()) // little endian, ���� �ּҿ� ���� �ڸ� ��, �������� ����ؾ� ��.
	{
		o << *itr; 
		itr++;
	}

	return o;
}

void moveTower(int from, int to, int rest, int size)
{
	if (size == 0)
	{
		return;
	}
	else
	{
		//
		moveTower(from, rest, to, size - 1);
		// move lowest level	
		tower[to].push(tower[from].top());
		tower[from].pop();
		std::cout << "\n" << from + 1 << " " << to + 1;
		//
		moveTower(rest, to, from, size - 1); 
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N;
	for (int i = N; i >= 1; --i)
	{
		tower[0].push(i);
	}
	BigInt result(1);
	for (int i = 0; i < N; ++i)
	{
		result * 2; // pow(2, N);
	}
	std::cout << (--result);
	
	if (N <= 20)
	{
		moveTower(0, 2, 1, N);
	}
}

BigInt& BigInt::operator*(int n) // �������� ū �� ����, ���ϴ� �� n�� 1�ڸ� ������ ����
{
	int carry = 0, digit = 0;
	for (int i = 0; i < numStr.size(); ++i)
	{
		carry += (numStr[i] - '0') * n;
		numStr[i] = '0' + (carry % 10);
		carry /= 10;
	}
	if (carry > 0)
	{
		numStr.push_back('0' + carry);
	}
	return *this;
}
BigInt& BigInt::operator--() // �������� ū �� ����, unsigned�� ���ؼ��� �۵���
{
	bool borrow = true;
	for (int i = 0; i < numStr.size(); ++i)
	{
		if (borrow && numStr[i] == '0')
		{
			numStr[i] = '9';
		}
		else if (borrow)
		{
			numStr[i]--;
			borrow = false;
		}
		else
		{
			break;
		}
	}
	return *this;
}
