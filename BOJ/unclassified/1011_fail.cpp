// �ð� �ʰ��� �غ��� �� ������
// ���� ���� �˰����� ���Ӱ� �����Ͽ� Ǯ���� �ʿ䰡 ����
// ������ �� distance�� ���� �̵� Ƚ���� ��Ģ���� �־���, �̸� Ȱ���ؾ� ��.

/*
#include<iostream>
#include<cmath>

int count_warp(int x, int y) {
	const int distance = y - x;
	int type_a = 0, a;
	int prev;
	for (a = 0; type_a <= distance; a++) {
		prev = type_a;
		type_a = pow(a + 1, 2);
	}
	type_a = prev; // ����
	a -= 2;

	int rest = distance - type_a;

	int counter = 2 * a + 1;  
	if (rest == 0) {
		return counter;
	}
	else if (rest > a + 1) {
		counter += 2;
		return counter;
	}
	else {
		// rest < a
		return ++counter;
	}

}

int main() {

	// test case
	//std::cout << count_warp(0, 4) << std::endl;

	int num_of_test;
	std::cin >> num_of_test;
	//scanf("%d", &num_of_test);
	//int* test_x = new int[num_of_test];
	//int* test_y = new int[num_of_test];
	int test_x[100];
	int test_y[100];

	for (int i = 0; i < num_of_test; i++) {
		//scanf("%d %d", &test_x[i], &test_y[i]);
		std::cin >> test_x[i] >> test_y[i];
	}

	for (int i = 0; i < num_of_test; i++) {
		std::cout << count_warp(test_x[i], test_y[i]) << std::endl;
		//printf("%d\n", count_warp(test_x[i], test_y[i]));
	}
	//delete[] test_x;
	//delete[] test_y;
}
*/