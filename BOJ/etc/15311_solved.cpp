#include <iostream>

/*
	boj 15311 �� �ȱ�

	������ �迭�� ����� ���ε�, �� �迭�� ������ ������ �����ؾ� ��

	"�ش� �迭�� ���ӵ� �κ��� ���� ������ 100�� ������ ��� ������ ���;� ��."
	"��, �迭�� ũ��� 2000�� �ִ���."

	========================================================
	���� ��ü�� �����̿���.

	"1"�� 1õ��, "1000"�� 1õ��....
*/
int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;
	std::string result;
	for (int i = 0; i < 1000; ++i)
		result.append("1 ");
	for (int i = 0; i < 1000; ++i)
		result.append("1000 ");
	std::cout << "2000\n" << result;
}