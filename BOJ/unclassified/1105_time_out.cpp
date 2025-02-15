/*
* ���� �¶��� ���� 1105��, 8
* �־��� ���� ���� ���ڵ� ��, 8�� ���� ���� ���� ����, 8�� ����ã��

* solution 1.
* �Ǵ� ����� �� ���ڿ� ���Ͽ�, 
* ���� 10���� ���� �������� Ȯ���Ͽ� 8�� �ִ����� Ȯ���غ���.
* 10���� ���� ���� �����ϰ�, �ٽ� 10���� ���� �������� Ȯ���Ѵ�
* �̸� �ݺ��Ͽ� 8�� ������ Ȯ���Ѵ�.
* fail, �ð� �ʰ�

#include<iostream>

int Left, Right;
int temp_result = 0;
int result = 9; // Right < 2000,000,000

int count_8_(int target) {
	if ((target % 10) == 8) {
		temp_result++;
	}
	// Ż�� ����
	if (target < 10) {
		return 0;
	}
	return count_8_(target / 10);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	// input
	std::cin >> Left >> Right;
	// calculation
	for (int i = Left; i <= Right; i++) {
		// i �� ���Ͽ� ���� �˻�
		count_8_(i);
		// �ִ� ����
		if (temp_result < result) {
			result = temp_result;
		}
		// �ӽð� �ʱ�ȭ
		temp_result = 0;
	}
	// output
	std::cout << result << '\n';
}

* solution 2.
* �Ǵ��� ������ ����ȭ �ϴ� ������ ���� ���� �ּ�ȭ ��Ų��.
* �Է����� �־��� �� ��谪�� ���ؼ� �Ǵ��Ѵ�.

#include<iostream>

int Left, Right;
int temp_result = 0;

int count_int_length(int n, int result = 0) {
	if ((n / 10) > 0) {
		return count_int_length(n / 10, result + 1);
	}
	else {
		return result;
	}
}

int count_8_(int l, int r) {
	// �� �� l, r�� �ڸ� ���� Ȯ����
	int s_l = count_int_length(l);
	int s_r = count_int_length(r);
	// �ڸ����� �ٸ��ٸ�, 0�� ����
	if (s_l != s_r) {
		return 0;
	}
	// �ڸ����� ���ٸ�,
	// l�� r�� �� �ڸ��� ���Ͽ� �����ϴ� �κп���
	// 8�� ������ ��� �����
	else {
		int result = 0;
		int den = [](int n)-> int {
			int pow = 1;
			for (int i = 0; i < n; i++) {
				pow *= 10;
			}
			return pow;
		}(s_l);
		for (int i = s_l; i >= 0; --i) {

			int j_l = l / den;
			int j_r = r / den;
			l -= j_l * den;
			r -= j_r * den;
			den /= 10;
			if (j_l == j_r) {
				if (j_l == 8) {
					result++;
				}
			}
			else {
				break;
			}
		}
		return result;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	// input
	std::cin >> Left >> Right;
	
	// test 
	//Left = 8808;
	//Right = 8889;
	 
	// calculation
	std::cout << count_8_(Left, Right) << '\n';
}

*/