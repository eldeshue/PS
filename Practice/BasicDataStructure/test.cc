#include <iostream>
#include "BaseNode.h"
#include "BaseList.h"
#include "MyStack.h"

class test_class
{
private:
  int *data;
  int length;

public:
  test_class(int size) : length(size)
  {
    data = new int[size];
  }

  ~test_class()
  {
    std::cout << "test objects destructor is called" << std::endl;
    delete[] data;
  }

  void show()
  {
    std::cout << length << std::endl;
    for (int i = 0; i < length; i++)
    {
      std::cout << data[i] << " ";
    }
    std::cout << std::endl;
  }
};

int main()
{
  BaseList<int> test1(1);
  test1.show_all_frontward();
  std::cout << "==========================" << std::endl;
  test1.enlist(2);
  test1.show_all_frontward();
  test1.enlist(3);
  test1.enlist(4);
  test1.enlist(5);
  std::cout << "==========================" << std::endl;
  test1.show_all_backward();
  std::cout << "==========================" << std::endl;
  test1.show_all_frontward();
}