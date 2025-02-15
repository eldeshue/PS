
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <functional>

using tree = std::tuple<int, int, int>;	// x, y, value
std::vector<tree> trees;	   // tree ������
std::vector<int> index_buffer; // trees�� �ε�����, Ʈ�� ��� ���ĵ�
std::function<bool(const int &, const int &)> sort_method[2];	// �Լ���ü, �Լ������� �迭�̶� �����ص� ��.

int pivot_x, pivot_y;	// pivot ���� ��ǥ
int div_x, div_y;		// ������ �̺��ϴ� div line�� ���⺤��

int dot(const int &idx)	// ������ �̺��ϴ� div ���� �������� ��ġ ����
{
	const int x = std::get<0>(trees[idx]) - pivot_x;
	const int y = std::get<1>(trees[idx]) - pivot_y;

	return (div_x * x + div_y * y);
}

int cross(const int &idx) // ������ �̺��ϴ� div ������ ��ġ ����
{
	const int x = std::get<0>(trees[idx]) - pivot_x;
	const int y = std::get<1>(trees[idx]) - pivot_y;

	return (x * div_y - y * div_x);
}

bool cmp_index_descend(const int &idx1, const int &idx2)
{
	int	priority1 = cross(idx1);
	int	priority2 = cross(idx2);
	if (priority1 == priority2)
	{
		priority1 = dot(idx1);
		priority2 = dot(idx2);
		return (priority1 > priority2);	// ���� ��� ��������
	}
	return (priority1 < priority2);	// ���� ��� ��������
}

bool cmp_index_ascend(const int &idx1, const int &idx2)
{
	int	priority1 = cross(idx1);
	int	priority2 = cross(idx2);
	if (priority1 == priority2)
	{
		priority1 = dot(idx1);
		priority2 = dot(idx2);
		return (priority1 < priority2);	// ���� ��� ��������
	}
	return (priority1 < priority2);	// ���� ��� ��������
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	sort_method[0] = cmp_index_descend;
	sort_method[1] = cmp_index_ascend;

	int N, total_value = 0, min_gap = 6e7;
	// �Է�
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		int x, y, val;
		std::cin >> x >> y >> val;
		total_value += val;
		trees.push_back(std::make_tuple(x, y, val));
		index_buffer.push_back(i);
	}
	// �� ������ ����, �� ������ �մ� ������ ���⸦ ������ �̺��ϴ� div line�� ����� ��´�
	for (int pivot_idx = 0; pivot_idx < N - 1; ++pivot_idx)
	{
		// pivot point, �� �� �� ����
		pivot_x = std::get<0>(trees[pivot_idx]);
		pivot_y = std::get<1>(trees[pivot_idx]);
		for (int target_idx = pivot_idx + 1; target_idx < N; ++target_idx)
		{
			// div line�� ���� ȹ��
			div_x = std::get<0>(trees[target_idx]) - pivot_x;
			div_y = std::get<1>(trees[target_idx]) - pivot_y;
			for (int sort_idx = 0; sort_idx < 2; ++sort_idx)
			{
				// sorting idx_buffer with divding line
				std::sort(index_buffer.begin(), index_buffer.end(), sort_method[sort_idx]);
				int sum = 0, cur_min_gap = total_value;
				for (int idx_idx = 0; idx_idx < N; ++idx_idx)
				{
					sum += std::get<2>(trees[index_buffer[idx_idx]]);
					int cur_gap = std::abs(total_value - sum * 2);
					if (cur_min_gap < cur_gap)
					{
						break;
					}
					cur_min_gap = cur_gap;
				}
				// get minimum gap value
				min_gap = std::min(min_gap, cur_min_gap);
			}
		}
	}
	std::cout << min_gap;
}
