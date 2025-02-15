// reconstruct tree
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> preOrders;
std::vector<std::string> inOrders;

void reconstPost(int vec_index, int in_begin, int in_end, int pre_root_index)
{
  const std::string &curPre = preOrders[vec_index];
  const std::string &curIn = inOrders[vec_index];
  // extract condition
  if (in_begin == in_end - 1)
  {
    std::cout << curIn[in_begin];
    return;
  }
  // calculate root index of inOrder
  int in_root_index = curIn.find(curPre[pre_root_index]);
  int left_length = in_root_index - in_begin;

  // left
  if (in_begin != in_root_index)
  {
    int pre_left_root_index = pre_root_index + 1;
    reconstPost(vec_index, in_begin, in_root_index, pre_left_root_index);
  }
  // right
  if (in_end - 1 != in_root_index)
  {
    int pre_right_root_index = pre_root_index + 1 + left_length;
    reconstPost(vec_index, in_root_index + 1, in_end, pre_right_root_index);
  }

  // root
  std::cout << curIn[in_root_index];
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  // get input
  std::string pre, in;
  while (std::cin >> pre >> in) // 입력의 개수가 주어지지 않은 경우 사용
  {                             // BOJ는 파일의 형태로 입력을 가하기에 다음 입력을 대기안함.
    preOrders.push_back(pre);
    inOrders.push_back(in);
  }
  // test case
  /*
  for (int i = 0; i < 2; ++i)
  {
    std::cin >> pre >> in;
    preOrders.push_back(pre);
    inOrders.push_back(in);
  }
  */

  for (int i = 0; i < inOrders.size(); ++i)
  {
    reconstPost(i, 0, inOrders[i].size(), 0);
    std::cout << "\n";
  }
}