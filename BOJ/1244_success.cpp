/*
#include<iostream>

class Switches {
private:
	int num_of_box;
	bool* box;

public:
	Switches(int n) : num_of_box(n) {
		box = new bool[n];
	}

	~Switches() {
		delete[] box;
	}

	void set(int loc, bool value) {
		box[loc] = value;
	}

	void change_switch(int loc) {
		// 0 to 1
		// 1 to 0
		box[loc] = !(box[loc]);
	}

	void Male_change(int base) {
		int loc = base - 1;
		while (loc < num_of_box) {
			change_switch(loc);
			loc += base;
		}
	}

	void Female_change(int center_loc) {
		// check symmetricalness of the switches
		change_switch(center_loc - 1);
		int right = center_loc;
		int left = center_loc - 2;
		while (left >= 0 && right < num_of_box) {
			if (box[left] == box[right]) {
				change_switch(left);
				change_switch(right);
				left--;
				right++;
			}
			else {
				break;
			}
		}
	}

	void print() {
		// print the status of switches 
		// print 20 switches on a line
		int line_counter = 0;

		for (int i = 0; i < num_of_box; i++) {
			std::cout << box[i] << " ";
			line_counter++;
			if (line_counter == 20) {
				std::cout << std::endl;
				line_counter = 0;
			}			
		}
	}

};

int main() {
	//test case//
	//int number_of_switches = 8;
	//Switches data(number_of_switches);
	//data.set(0, 0);
	//data.set(1, 1);
	//data.set(2, 0);
	//data.set(3, 1);
	//data.set(4, 0);
	//data.set(5, 0);
	//data.set(6, 0);
	//data.set(7, 1);
	//data.Male_change(3);
	//data.Female_change(3);
	
	// main
	// input
	// 1 : number of switches
	int number_of_switches;
	std::cin >> number_of_switches;
	Switches data(number_of_switches);
	// 2 : initial status of the switches
	for (int i = 0; i < number_of_switches; i++) {
		bool value;
		std::cin >> value;
		data.set(i, value);
	}
	// 3 : number_of_students
	int number_of_students;
	std::cin >> number_of_students;
	
	// calculation
	for (int i = 0; i < number_of_students; i++) {
		int gender, location;
		std::cin >> gender;
		std::cin >> location;
		switch (gender) {
			case 1:
				// male
				data.Male_change(location);
				break;
			case 2:
				// female
				data.Female_change(location);
				break;
			default:
				break;
		}	
	}

	// output
	data.print();

	return 0;
}
*/