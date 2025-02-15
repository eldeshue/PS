// 백준 2941번 크로아티아 알파벳 문제
/*
#include<iostream>
#include<string>

int main() {
	// input
	std::string word;
	std::cin >> word;
	int counter = 0;
	int index = 0;
	while (index < word.length()) {
		if (index == word.length() - 1) {
			counter++;
			break;
		}
		char now = word[index];
		char next = word[index + 1];
		switch (now) {
		case 'c':
			if (next == '=' || next == '-') {
				index++;
			}
			break;
		case 'd':
			if ( next == '-') {
				index++;
			}
			if (next == 'z') {
				if (index + 1 == word.length()) break;
				if(word[index + 2] == '=') index = index + 2;
			}
			break;
		case 'l':
			if (next == 'j') {
				index++;
			}
			break;
		case 'n':
			if (next == 'j') {
				index++;
			}
			break;
		case 's':
			if (next == '=') {
				index++;
			}
			break;
		case 'z':
			if (next == '=') {
				index++;
			}
			break;
		}
		counter++;
		index++;
	}

	std::cout << counter;
}

*/