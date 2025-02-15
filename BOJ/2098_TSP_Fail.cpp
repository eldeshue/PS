// ���� 2098��, ���ǿ� ��ȸ ����(Traveling Salesman Problem)
// ��ó1 : https://withhamit.tistory.com/246
// ��ó2 : https://yabmoons.tistory.com/358

// ��Ʈ����ŷ
// ������ 2���� ǥ���� ������ �����̳ʷ� �����.
// ��Ʈ�����̶� �� �ӵ��� �ſ� ������
// �������� �޸��� ��뷮�� �ſ� ��� TSP�� ������ȹ�� �ſ� �����ϴ�.

// ��Ʈ ������
// & : and, �������� �� �츦 �� ��Ʈ�� ���Ͽ� �� �� true�� ��� true�� �Ҵ�
// | : or, �������� �� �츦 �� ��Ʈ�� ���Ͽ� �� �� �ϳ��� true�� true�� �Ҵ�
// ^ : xor, �������� �� �츦 �� ��Ʈ�� ���Ͽ� �� �� �ϳ��� true�϶��� true
// ~ : not, ���� ��Ʈ�� ���¸� �ٲ۴�.
// << >> : shift, ���� �������� �����ϴ� ��Ʈ�� �ڸ��� �̵��Ѵ�.

// 1 << k : k ��° ��ġ�� ��Ʈ�� ���Ͽ�....
// A &=  ~() : ����
// A |= () : �߰�
// A ^= () : ����, ���
// if(A & (1 << k))  : ���� ���� Ȯ��

/*
#include<iostream>

int city_num;
int price_data[16][16];
int status_min_cost[16][1 << 16] = { 0 };

const int max = 17000000;
// ������ ���� ��ġ
// ���� ���ݱ��� ���Ŀ� ���� ���� status
// 2���� �迭�� ������ ���ݱ��� ���Ŀ� ����� �ּڰ��� ������

int TSP(int visit_route, int now_city) {
	// ����Լ�
	// ���� ���ô� 0������ ���� 

	// �Է¹��� ���� ���� ���,  
	visit_route |= (1 << now_city);

	// Ż������ - status ���� 2^city_num - 1�� ���,
	if (visit_route == (1 << city_num) - 1) {
		// 1. ������, 0������ ���ƿ��� ���� ���� ���
		if (price_data[now_city][0] > 0) {
			// ����, ���� ��� ��ȯ
			return price_data[now_city][0];
		}

		return max; // fail
	}

	// �޸������̼�
	// ���� �������� �ƴ� ���, �� �Ϲ����� ������ ���Ͽ�
	int& ret = status_min_cost[now_city][visit_route];
	if (ret > 0)
		return ret;

	// ���� ������ ret, ���� ��α��� �ּ� ��밪�� 0�̶��,
	// �� ���� ����� �ּڰ��� ã���� ���� ���� ��쿡
	ret = max;

	for (int i = 0; i < city_num; i++) {

		if (i != now_city && // ���� ���÷δ� �������� �ȵ�.
			(visit_route & (1 << i)) == 0 && //�̹� ������ ���ô� �ȵ�
			price_data[now_city][i] > 0) { // ��ΰ� �ִ� ���ø� ��

			// �ּڰ� ����
			int temp = TSP(visit_route, i) + price_data[now_city][i];
			if (ret > temp)
				ret = temp;
		}

	}
	return ret;

}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL); // ����� ����ȭ, �̱۽�����

	// input
	std::cin >> city_num;
	for (int i = 0; i < city_num; i++) {
		for (int j = 0; j < city_num; j++) {
			std::cin >> price_data[i][j];
		}
	}

	std::cout << TSP(0,0) << '\n';
}
*/