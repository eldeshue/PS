// 拷層 1557腰 庚薦, 薦咽 いい 呪
// 薦咽 いい 呪空, 1戚 焼観 薦咽 呪稽 蟹刊嬢 走走 省澗 呪戚陥.
// 聡 背雁 呪澗 1戚 焼観 薦咽 呪研 昔切稽 握走 省澗 呪研 源廃陥.


#include<iostream>
#include<vector>
#include<cmath>

class K {
private:
	int k, now_square_nn; // now_square_nn 薄仙 姥廃 節仙旋 薦咽 いい呪
	int previous_square_nn = 2;
	int biggest_square_yy = 0; // 走榎猿走 達精 亜舌 笛 薦咽 しし呪	
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
				//社呪亜 焼艦虞檎, false
				return false;
			}
		}
		//社呪亜 限陥檎, true
		return true;
	}

	void Find_new_prime() {
		// sqrt(now_square_nn) 左陥 拙精 歯稽錘 社呪研 達焼辞 
		// 背雁 社呪研 達生檎 prime拭 蓄亜廃陥.

		for (int i = previous_max_prime; i < std::sqrt(now_square_nn); i++) {
			if (check_prime(i)) {
				prime.push_back(i);
				previous_max_prime = i;
			}

		}

	}

	bool check_square_yy(int target) {
		// 背雁 収切亜 薦咽しし 戚檎 true研 鋼発馬奄
		for (const auto& prime_num : prime) {
			if (target % (prime_num * prime_num) == 0) {
				return true;
			}
		}
		return false;
	}

	// 仙瑛旋生稽 溌昔 貢 端滴.
	int Find_square_nn() {
		
		int new_square_yy_num = 0;
		// 歯稽錘 社呪 達奄
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

		// previous_square_nn 引 now_square_nn 紫戚税 square_yy研 達焼辞 蓄亜馬檎 喫.
		int i = previous_square_nn + 1;
		while (i <= now_square_nn) {
			if (check_square_yy(i)) { // yy戚檎 蓄亜
				new_square_yy_num++;
			}
			i++;
		}


		// 脊径閤精 k 拭 企馬食, k左陥 拙精 薦咽呪税 壕呪級聖 乞砧 薦須廃陥.
		// 聡, 薦須廃 呪 幻鏑 result拭 希背層陥.
		// 希背層 result拭澗 歯稽錘 薦咽 しし 呪亜 匂敗吉陥.
		// 陥獣 杏君爽嬢醤 原競馬陥.
		previous_square_nn = now_square_nn;
		now_square_nn += new_square_yy_num;
		// 幻鉦 薄仙 薦咽いい呪亜 k腰属亜 溌叔馬陥檎, 
		// 蓄亜稽 達焼走澗 薦咽 しし 呪亜 蒸陥檎
		// loop研 纏窒廃陥.
		if (new_square_yy_num == 0) {
			return now_square_nn;
		}
		else {			
			return Find_square_nn();
		}
	}
};


int main() {
	// 脊径
	int k;	
	std::cin >> k;
	//k = 1234567; // 
	// 段奄葵 竺舛
	K solution(k);

	// 姥薄
	// 庚薦澗 脊径閤精 k腰属拭 背雁馬澗 薦咽 いい呪研 達奄研 郊空陥.
	// k 猿走税 呪 掻拭辞 薦咽聖 昔切稽 握澗 呪税 姐呪幻鏑聖 希廃陥.
	// 希廃 呪 掻拭辞 薦咽聖 昔切稽 握澗 呪税 姐呪幻鏑聖 希廃陥.
	// 
	// 拙精 授辞採斗, 薦咽聖 昔切稽 握澗 呪, 薦咽 しし呪研 達澗陥
	// 薦咽しし 呪 : 4 8 9 12 16 18 20 24 25 ....

	// 脊径閤精 k 拭 企馬食, k左陥 拙精 薦咽呪税 壕呪級聖 乞砧 薦須廃陥.
	// 薦須廃 呪 幻鏑 k拭 希背層陥.

	// 窒径
	std::cout << solution.Find_square_nn();
	
}



