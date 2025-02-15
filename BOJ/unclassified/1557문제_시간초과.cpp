// ���� 1557�� ����, ���� ���� ��
// ���� ���� ����, 1�� �ƴ� ���� ���� ������ ���� �ʴ� ���̴�.
// �� �ش� ���� 1�� �ƴ� ���� ���� ���ڷ� ���� �ʴ� ���� ���Ѵ�.


#include<iostream>
#include<vector>
#include<cmath>

class K {
private:
	int k, now_square_nn; // now_square_nn ���� ���� ������ ���� ������
	int previous_square_nn = 2;
	int biggest_square_yy = 0; // ���ݱ��� ã�� ���� ū ���� ������	
	int previous_j = 1;

	int previous_max_prime = 2;
	std::vector<int> prime;

public:
	K(int k) :k(k),now_square_nn(k) {
		prime.push_back(2);
	};
	~K() {};

	bool check_prime(int target) {
		
		for (const auto& p : prime) {
			if (target % p == 0) {
				//�Ҽ��� �ƴ϶��, false
				return false;
			}
		}
		//�Ҽ��� �´ٸ�, true
		return true;
	}

	void Find_new_prime() {
		// sqrt(now_square_nn) ���� ���� ���ο� �Ҽ��� ã�Ƽ� 
		// �ش� �Ҽ��� ã���� prime�� �߰��Ѵ�.

		for (int i = previous_max_prime; i < std::sqrt(now_square_nn); i++) {
			if (check_prime(i)) {
				prime.push_back(i);
				previous_max_prime = i;
			}

		}

	}

	bool check_square_yy(int target) {
		// �ش� ���ڰ� �������� �̸� true�� ��ȯ�ϱ�
		for (const auto& prime_num : prime) {
			if (target % (prime_num * prime_num) == 0) {
				return true;
			}
		}
		return false;
	}

	// ��������� Ȯ�� �� üũ.
	int Find_square_nn() {
		
		int new_square_yy_num = 0;
		// ���ο� �Ҽ� ã��
		Find_new_prime();

		//for ( const auto& i : prime) {
		//	for (int j = previous_j; i * i * j <= now_square_nn; j++) {
		//		if (i * i * j > biggest_square_yy) {
		//			previous_j = j;
		//			biggest_square_yy = i * i * j;
		//			new_square_yy_num++;
		//		}				
		//	}
		//}

		// previous_square_nn �� now_square_nn ������ square_yy�� ã�Ƽ� �߰��ϸ� ��.
		int i = previous_square_nn + 1;
		while (i <= now_square_nn) {
			if (check_square_yy(i)) { // yy�̸� �߰�
				new_square_yy_num++;
			}
			i++;
		}


		// �Է¹��� k �� ���Ͽ�, k���� ���� �������� ������� ��� �����Ѵ�.
		// ��, ������ �� ��ŭ result�� �����ش�.
		// ������ result���� ���ο� ���� ���� ���� ���Եȴ�.
		// �ٽ� �ɷ��־�� �����ϴ�.
		previous_square_nn = now_square_nn;
		now_square_nn += new_square_yy_num;
		// ���� ���� ������������ k��°�� Ȯ���ϴٸ�, 
		// �߰��� ã������ ���� ���� ���� ���ٸ�
		// loop�� Ż���Ѵ�.
		if (new_square_yy_num == 0) {
			return now_square_nn;
		}
		else {			
			return Find_square_nn();
		}
	}
};


int main() {
	// �Է�
	int k;	
	std::cin >> k;
	//k = 1234567; // 
	// �ʱⰪ ����
	K solution(k);

	// ����
	// ������ �Է¹��� k��°�� �ش��ϴ� ���� �������� ã�⸦ �ٶ���.
	// k ������ �� �߿��� ������ ���ڷ� ���� ���� ������ŭ�� ���Ѵ�.
	// ���� �� �߿��� ������ ���ڷ� ���� ���� ������ŭ�� ���Ѵ�.
	// 
	// ���� ��������, ������ ���ڷ� ���� ��, ���� �������� ã�´�
	// �������� �� : 4 8 9 12 16 18 20 24 25 ....

	// �Է¹��� k �� ���Ͽ�, k���� ���� �������� ������� ��� �����Ѵ�.
	// ������ �� ��ŭ k�� �����ش�.

	// ���
	std::cout << solution.Find_square_nn();
	
}



