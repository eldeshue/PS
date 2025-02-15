// failed. out of memory.
#include <iostream>
#include <string>

// sizeof(int_node) = 24, 1000개가 max이므로, 최대 24KB.
typedef struct int_node
{
  int nValue;
  int nindex;
  int_node *pLeft;
  int_node *pRight;
} int_node;

// sizeof(RoundQueue) = 24
class RoundQueue
{
private:
  int size;
  int next_move;
  int_node *head;
  int_node *current_node;

public:
  RoundQueue(int n) : size(1), next_move(0), head(new int_node), current_node(head)
  {
    head->nValue = n;
    head->nindex = 1;
    head->pLeft = head;
    head->pRight = head;
  }
  ~RoundQueue()
  {
    while (size > 1)
    {
      dislink(head->pLeft);
      size--;
    }
    delete head;
  }
  void put_new_node(int value, int index)
  {
    int_node *new_node = new int_node;
    new_node->pLeft = head->pLeft;
    new_node->pRight = head;

    head->pLeft = new_node;
    head->pLeft->pLeft->pRight = new_node;

    new_node->nValue = value;
    new_node->nindex = index;

    size++;
  }

  void dislink(int_node *target_node)
  {
    if (target_node == head)
    {
      head = head->pLeft;
    }
    target_node->pRight->pLeft = target_node->pLeft;
    target_node->pLeft->pRight = target_node->pRight;

    delete target_node;
  }

  void mov_and_pop()
  {
    // mov
    int_node *target = current_node;
    next_move = target->nValue;
    if (next_move >= 0)
    {
      for (int i = 0; i < next_move % size; ++i)
      {
        current_node = current_node->pRight;
      }
    }
    else
    {
      int abs_n = std::abs(next_move);
      for (int i = 0; i < abs_n % size; ++i)
      {
        current_node = current_node->pLeft;
      }
    }

    // pop
    std::cout << target->nindex << " ";
    dislink(target);
    size--;
  }

  int get_head_index()
  {
    return head->nindex;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int total_size = 1000;
  // std::cin >> total_size;

  int temp = 1;
  // std::cin >> temp;
  RoundQueue balloons(temp);
  for (int i = 2; i <= total_size; ++i)
  {
    // std::cin >> temp;
    temp = 1;
    balloons.put_new_node(temp, i);
  }

  for (int i = 1; i < total_size; ++i)
  {
    balloons.mov_and_pop();
  }

  std::cout << balloons.get_head_index() << " " << std::endl;
}
