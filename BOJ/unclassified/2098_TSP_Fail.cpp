// 백준 2098번, 외판원 순회 문제(Traveling Salesman Problem)
// 출처1 : https://withhamit.tistory.com/246
// 출처2 : https://yabmoons.tistory.com/358

// 비트마스킹
// 정수의 2진수 표현을 일종의 컨테이너로 사용함.
// 비트연산이라 그 속도가 매우 빠르다
// 무엇보다 메모리의 사용량이 매우 적어서 TSP의 동적계획에 매우 적합하다.

// 비트 연산자
// & : and, 연산자의 좌 우를 한 비트씩 비교하여 둘 다 true인 경우 true를 할당
// | : or, 연산자의 좌 우를 한 비트씩 비교하여 둘 중 하나만 true라도 true를 할당
// ^ : xor, 연산자의 좌 우를 한 비트씩 비교하여 둘 중 하나만 true일때만 true
// ~ : not, 현재 비트의 상태를 바꾼다.
// << >> : shift, 현재 정수에서 존재하는 비트의 자리를 이동한다.

// 1 << k : k 번째 위치의 비트에 대하여....
// A &=  ~() : 제거
// A |= () : 추가
// A ^= () : 반전, 토글
// if(A & (1 << k))  : 존재 여부 확인

/*
#include<iostream>

int city_num;
int price_data[16][16];
int status_min_cost[16][1 << 16] = { 0 };

const int max = 17000000;
// 행으로 현재 위치
// 열로 지금까지 거쳐온 도시 상태 status
// 2차원 배열의 값으로 지금까지 거쳐온 경로의 최솟값을 저장함

int TSP(int visit_route, int now_city) {
	// 재귀함수
	// 시작 도시는 0번으로 고정 

	// 입력받은 현재 도시 통과,  
	visit_route |= (1 << now_city);

	// 탈출조건 - status 값이 2^city_num - 1인 경우,
	if (visit_route == (1 << city_num) - 1) {
		// 1. 시작점, 0번으로 돌아오는 길이 없는 경우
		if (price_data[now_city][0] > 0) {
			// 성공, 여행 비용 반환
			return price_data[now_city][0];
		}

		return max; // fail
	}

	// 메모이제이션
	// 가장 마지막이 아닌 경우, 즉 일반적인 참조에 대하여
	int& ret = status_min_cost[now_city][visit_route];
	if (ret > 0)
		return ret;

	// 만약 참조한 ret, 현재 경로까지 최소 비용값이 0이라면,
	// 즉 아직 경로의 최솟값이 찾아진 적이 없는 경우에
	ret = max;

	for (int i = 0; i < city_num; i++) {

		if (i != now_city && // 현재 도시로는 움직여선 안됨.
			(visit_route & (1 << i)) == 0 && //이미 지나간 도시는 안됨
			price_data[now_city][i] > 0) { // 경로가 있는 도시만 됨

			// 최솟값 갱신
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
	std::cout.tie(NULL); // 입출력 최적화, 싱글스레드

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