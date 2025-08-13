
/*
	BOJ 14572
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <tuple>

using Stat = std::pair<int, int>;	// D, id

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, M, K, D;
	std::cin >> N >> K >> D;
	std::vector<Stat> students(N);
	std::vector<std::vector<int>> subjects(N);
	for (int id = 0; id < N; ++id)
	{
		std::cin >> M >> students[id].first;
		students[id].second = id;
		subjects[id] = std::vector<int>(M);
		for (auto& m : subjects[id])
			std::cin >> m;
	}

	// sort by d
	std::sort(students.begin(), students.end());

	// greedy, two pointer
	std::array<int, 31> cur_subjects;
	std::fill(cur_subjects.begin(), cur_subjects.end(), 0);
	int result = 0, l = 0;
	for (int r = 0; r < N; ++r)
	{
		while (/*l < r && */D < (students[r].first - students[l].first))
		{
			// sub left, update
			for (auto sub : subjects[students[l].second])
				--cur_subjects[sub];
			++l;
		}
		// add right, update
		for (auto add : subjects[students[r].second])
			++cur_subjects[add];

		int const group_size = r - l + 1;
		int known_by_group = 0, known_by_all = 0;
		for (int cnt : cur_subjects)
		{
			if (cnt > 0)
				known_by_group++;
			if (cnt == group_size)
				known_by_all++;
		}

		// update result
		result = std::max(result, (known_by_group - known_by_all) * group_size);
	}
	std::cout << result;
}

