
/*

	boj 1522, ���ڿ� ��ȯ

	a,b�� �� ���ڷ� �̷���� ���ڿ��� ���ӵ� a�� ����� ���� swap�� �ּ�Ƚ��
	�����̵� ������ ������� Ǯ�̰� ������.

	�����̵� ������� �� �������� ����, �� �� �������� �Ÿ��� �����ϴٴ� ���̰� ����.

	�ش� ������ �ּ�Ƚ���� ���Ϸ��� �ϴ� ���� ���� ��ģ ���(���� ��� ����)�� ã��,
	�ش� ����� ������� ��. ��.��� ���ڷ� ������ �ϴ����� ���ڿ� ���¿� ���� �ٸ�.
	
	���� ���� �������� ���� ū ����� ã�Ƽ�, �ش� ����� �� ��� �ִ� ũ���� ���� ���ϸ� ��.

	�߰������� ���ڿ��� round buffer�� ���¶�� ������ �����Ƿ�, �̸� ���ؼ� �����̵� �����츦 
	���� ��������� ��.

*/

#include <iostream>
#include <string>

int sliding_window(const std::string& str, char c, int window_size)
{
	int end, max_cnt = 0, cnt = 0;
	for (int i = 0; i < window_size; ++i)
	{
		if (str[i] == c)
			cnt++;
	}
	max_cnt = cnt;
	for (int start = 1; start < str.size(); ++start)
	{
		end = (start + window_size - 1) % str.size();	// round-buffer.
		if (str[start - 1] == c)
			cnt--;
		if (str[end] == c)
			cnt++;
		max_cnt = std::max(max_cnt, cnt);
	}
	return window_size - max_cnt;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int max_a = 0, max_b = 0;
	std::string str;
	std::cin >> str;
	for (char c : str)
	{
		if (c == 'a')
			max_a++;
		else
			max_b++;
	}
	// sliding window, X2
	// O(2N)
	std::cout << std::min(sliding_window(str, 'a', max_a), sliding_window(str, 'b', max_b));
}