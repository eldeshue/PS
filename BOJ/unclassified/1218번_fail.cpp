// 백준 1218번, Robot
/*
#include<iostream>

struct point {
	int x;
	int y;
	point():x(0),y(0) {}
	point(int x, int y) : x(x), y(y) {}
};
struct line {
	point p1; // 왼쪽, 또는 아랫쪽
	point p2; // 오른쪽, 또는 윗쪽
	bool is_vertical;
	int axis_value;
	line(){}
	line (point p1, point p2){
		if (p1.x == p2.x) { 
			is_vertical = true; 
			axis_value = p1.x;
			if (p1.y < p2.y) { // 정렬해서 저장
				this->p1 = p1;
				this->p2 = p2;
			}
			else {
				this->p1 = p2;
				this->p2 = p1;
			}
		}
		else { 
			is_vertical = false; 
			axis_value = p1.y;
			if (p1.x < p2.x) { // 정렬해서 저장
				this->p1 = p1;
				this->p2 = p2;
			}
			else {
				this->p1 = p2;
				this->p2 = p1;
			}
		}
	}
};
struct route {
	line l1;
	line l2;
	route() {};
	route(line l1, line l2) : l1(l1), l2(l2) {};
};
class field {
public:
	int num_of_corner;
	point* corner = nullptr;
	line* wall = nullptr;
	point axis[5];

//public:
	field( int n ) : num_of_corner(n) {
		corner = new point[n];
		wall = new line[n];
	}
	~field(){
		if (corner != nullptr) {
			delete[] corner;
			delete[] wall;
			corner = nullptr;
		}		
	}
	void set_corner(int i, point& p) {
		corner[i] = p;
	}

	void set_corner(int i, point&& p) {
		corner[i] = p;
	}

	void set_axis(int i, point& p) {
		axis[i] = p;
	}

	void set_axis(int i, point&& p) {
		axis[i] = p;
	}

	void set_wall() {
		for (int i = 0; i < num_of_corner - 1; i++) {
			wall[i] = line(corner[i], corner[i + 1]);
		}
		wall[num_of_corner - 1] = line(corner[num_of_corner - 1], corner[0]);
	}

	bool check_cross(route r, line wall) { 
		// 교차하려면, is_vertical 값이 달라야 함.
		if (wall.is_vertical != r.l1.is_vertical) {
			// wall & l1 수직
			if (((wall.axis_value > r.l1.p1.x && wall.axis_value < r.l1.p2.x) &&
				(r.l1.axis_value > wall.p1.y && r.l1.axis_value < wall.p2.y))
				||
				((wall.axis_value > r.l1.p1.y && wall.axis_value < r.l1.p2.y) &&
				(r.l1.axis_value > wall.p1.x && r.l1.axis_value < wall.p2.x))) {
				// 교차한다
				return true;
			}
			
		}
		else {
			// wall & l2 수직
			if (((wall.axis_value > r.l2.p1.x && wall.axis_value < r.l2.p2.x) &&
				(r.l2.axis_value > wall.p1.y && r.l2.axis_value < wall.p2.y))
				||
				((wall.axis_value > r.l2.p1.y && wall.axis_value < r.l2.p2.y) &&
				(r.l2.axis_value > wall.p1.x && r.l2.axis_value < wall.p2.x))) {
				// 교차한다
				return true;
			}		
			
		}
		// 최후까지 교차하지 않는다.
		return false;
	}

	bool check_axis(int axis_num) { // 시작점

		// 두 번의 더하기 및 빼기를 통해서 모든 코너에 이를 수 있는가?
		// 한 점에서 다른 점으로 이동하는데, 한 번의 방향전환만 가능하다면 그 가짓수는 2
		// 각 axis에 대하여, 목적으로 하는 코너당 2개의 경로가 벽과 교차하는지 체크할것
		// 만약 wall 과 route가 교차한다면, 이는 fail

		// route 1, 2 생성
		// 두 점 p1 p2에 대하여
		// route 1 : x1 y1 - x1 y2 - x2 y2
		// route 2 : x1 y1 - x2 y1 - x2 y2
		// 선분은 두 점의 연결을 통해서 생겨나며, 두 선의 교차를 검증하기 위해서는 
		// 4개의 점이 필요하다.
		for (int goal = 0; goal < num_of_corner; goal++) { // 끝점			
			// axis와 goal, 두 점을 통해서 두개의 route 생성
			// 두 루트에 대하여 각 wall들과 교차 여부를 체크한다.
			route route1(line(axis[axis_num], point(axis[axis_num].x, corner[goal].y)),
				line(point(axis[axis_num].x, corner[goal].y), corner[goal]));
			
			route route2(line(axis[axis_num], point(corner[goal].x, axis[axis_num].y)),
				line(point(corner[goal].x, axis[axis_num].y), corner[goal]));

			for (int wall_num = 0; wall_num < num_of_corner; wall_num++) {
				if ((this->check_cross(route1, wall[wall_num]) 
					&& 
					this->check_cross(route2, wall[wall_num]))) {					
					return false;
				}
			}		
			
		}		
		return true;
	}

};


bool check_cross_line(line l1, line l2) {
	if (((l1.axis_value >= l2.p1.x && l2.axis_value <= l2.p2.x) &&
		(l2.axis_value >= l1.p1.y && l2.axis_value <= l1.p2.y))
		||
		((l1.axis_value >= l2.p1.y && l2.axis_value <= l2.p2.y) &&
			(l2.axis_value >= l1.p1.x && l2.axis_value <= l1.p2.x))) {
		// 교차한다
		return true;
	}
	return false;
}

bool check_cross_route(route r, line wall) {
	// 교차하려면, is_vertical 값이 달라야 함.
	if (wall.is_vertical != r.l1.is_vertical) {
		// wall & l1 수직
		if (((wall.axis_value >= r.l1.p1.x && wall.axis_value <= r.l1.p2.x) &&
			(r.l1.axis_value >= wall.p1.y && r.l1.axis_value <= wall.p2.y))
			||
			((wall.axis_value >= r.l1.p1.y && wall.axis_value <= r.l1.p2.y) &&
				(r.l1.axis_value >= wall.p1.x && r.l1.axis_value <= wall.p2.x))) {
			// 교차한다
			return true;
		}
		return false;
	}
	else {
		// wall & l2 수직
		if (((wall.axis_value >= r.l2.p1.x && wall.axis_value <= r.l2.p2.x) &&
			(r.l2.axis_value >= wall.p1.y && r.l2.axis_value <= wall.p2.y))
			||
			((wall.axis_value >= r.l2.p1.y && wall.axis_value <= r.l2.p2.y) &&
				(r.l2.axis_value >= wall.p1.x && r.l2.axis_value <= wall.p2.x))) {
			// 교차한다
			return true;
		}
		return false;
	}
	// 최후까지 교차하지 않는다.
	
}


int main() {
	
	// 테스트 케이스
	
	//point p1(3, 4);
	//point p2(3, 16);
	//point p3(0, 16);
	//point p4(20, 16);
	//
	//
	//line l1(p1, p2);
	//line l2(p3, p4);
	//std::cout << check_cross_line(l1, l2) << std::endl;
	//
	//
	//point p1(3, 4);
	//point p2(16, 4);
	//point p3(16, 25);
	//
	//route r1(line(p1, p2), line(p2, p3));
	//
	//point p4(16, 0);
	//point p5(16, 25);
	//
	//line wall1(p4, p5);
	//
	//std::cout << check_cross_route(r1, wall1) << std::endl;
	//
	//
	//
	//// test case2
	//int test_num_of_corner = 8;
	//field test_Room(test_num_of_corner);
	//point p1(0, 0);
	//point p2(20, 0);
	//point p3(20, 20);
	//point p4(30, 20);
	//point p5(30, 0);
	//point p6(40, 0);
	//point p7(40, 40);
	//point p8(0, 40);
	//test_Room.set_corner(0, p1);
	//test_Room.set_corner(1, p2);
	//test_Room.set_corner(2, p3);
	//test_Room.set_corner(3, p4);
	//test_Room.set_corner(4, p5);
	//test_Room.set_corner(5, p6);
	//test_Room.set_corner(6, p7);
	//test_Room.set_corner(7, p8);
	//point a1(10, 10);
	//point a2(25, 30);
	//point a3(35, 10);
	//point a4(5, 30);
	//point a5(10, 20);
	//test_Room.set_axis(0, a1);
	//test_Room.set_axis(1, a2);
	//test_Room.set_axis(2, a3);
	//test_Room.set_axis(3, a4);
	//test_Room.set_axis(4, a5);
	//test_Room.set_wall();
	//
	//route route1(line(test_Room.axis[0], point(test_Room.axis[0].x, test_Room.corner[4].y)),
	//	line(point(test_Room.axis[0].x, test_Room.corner[4].y), test_Room.corner[4]));
	//
	//route route2(line(test_Room.axis[0], point(test_Room.corner[4].x, test_Room.axis[0].y)),
	//	line(point(test_Room.corner[4].x, test_Room.axis[0].y), test_Room.corner[4]));
	//
	//std::cout << test_Room.wall[1].p1.x << " " << test_Room.wall[1].p1.y << std::endl;
	//std::cout << test_Room.wall[1].p2.x << " " << test_Room.wall[1].p2.y << std::endl;
	//std::cout << test_Room.wall[1].axis_value << std::endl;
	//// 성공
	//std::cout << test_Room.check_cross(route1, test_Room.wall[1]) << std::endl;
	//// 실패
	//// 경계에 걸치면 답이 없다!!!!
	//std::cout << test_Room.check_cross(route2, test_Room.wall[1]) << std::endl;
	
	
	//for (int i = 0; i < 5; i++) {
	//	if (test_Room.check_axis(i)) { // 모든 goal에 대해 교차하지 않아야 YES임
	//		std::cout << "YES" << std::endl;
	//	}
	//	else {
	//		std::cout << "NO" << std::endl; // 최소 하나의 goal도 교차하면 NO임
	//	}
	//}
	

	
	// main
	int num_of_corner;
	std::cin >> num_of_corner;
	field Room(num_of_corner);
	for (int i = 0; i < num_of_corner; i++) {
		int x, y;
		std::cin >> x;
		std::cin >> y;
		Room.set_corner(i,point(x, y));
	}
	Room.set_wall();
	for (int i = 0; i < 5; i++) {
		int x, y;
		std::cin >> x;
		std::cin >> y;
		Room.set_axis(i, point(x, y));
	}
	for (int i = 0; i < 5; i++) {
		if (Room.check_axis(i)) { // 모든 goal에 대해 교차하지 않아야 YES임
			std::cout << "YES" << std::endl;
		}
		else {
			std::cout << "NO" << std::endl; // 최소 하나의 goal도 교차하면 NO임
		}
	}
	
		
}

*/