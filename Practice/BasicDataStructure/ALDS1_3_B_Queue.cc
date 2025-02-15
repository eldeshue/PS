// simulating Round Robin Scheduling algorithm

#include <iostream>
#include <string>
#include "MyRoundQueue.h"

class PCB
{
private:
  std::string process_name;
  int remain_time;

public:
  PCB(std::string name, int tq) : process_name(name), remain_time(tq){};
  PCB(const PCB &p)
  {
    process_name = p.process_name;
    remain_time = p.remain_time;
  }
  PCB(PCB &&p)
  {
    process_name = p.process_name;
    remain_time = p.remain_time;
  }
  ~PCB(){};

  PCB &operator=(const PCB &p)
  {
    process_name = p.process_name;
    remain_time = p.remain_time;

    return *this;
  }

  int get_remain_time() { return remain_time; }

  void show(int current_time)
  {
    std::cout << process_name << " " << current_time << "\n";
  };

  int spend_time(int t)
  {
    if (remain_time <= t)
    {
      int result = remain_time;
      remain_time = 0;
      return result;
    }
    remain_time -= t;
    return t;
  };
};

class ProcessQueue : public MyRoundQueue<PCB>
{
private:
  BaseNode<PCB> *current_node;

public:
  PCB &get_current_node()
  {
    if (current_node)
    {
      return current_node->get();
    }
    return this->front_node->get();
  }
  void set_current_node(int index = 0)
  {
    current_node = this->front_node;

    for (int i = 0; i < index % this->num_of_elem; i++)
    {
      current_node = current_node->get_next_node();
    }
  }
  void move_next_node(int current_time)
  {

    if (current_node->get().get_remain_time() == 0)
    {
      current_node->get().show(current_time);
      BaseNode<PCB> *temp = current_node->get_next_node();
      current_node->dislink_node();
      current_node = temp;
      this->num_of_elem--;
    }
    else
    {
      current_node = current_node->get_next_node();
    }
  }
};

int main()
{
  ProcessQueue ReadyQueue;

  /*
  int num_of_process;
  int time_quantum;
  std::cin >> num_of_process;
  std::cin >> time_quantum;

  std::string process_name;
  int process_time;
  for (int i = 0; i < num_of_process; i++)
  {
    std::cin >> process_name;
    std::cin >> process_time;
    ReadyQueue.push_back(PCB(process_name, process_time));
  }

  std::cout << std::endl;
  */
  // test
  int num_of_process = 5;
  int time_quantum = 100;
  ReadyQueue.push_back(PCB("p1", 150));
  ReadyQueue.push_back(PCB("p2", 80));
  ReadyQueue.push_back(PCB("p3", 200));
  ReadyQueue.push_back(PCB("p4", 350));
  ReadyQueue.push_back(PCB("p5", 20));

  ReadyQueue.set_current_node();

  int accum_time = 0;
  while (!ReadyQueue.is_empty())
  {
    PCB &target_process = ReadyQueue.get_current_node();

    accum_time += target_process.spend_time(time_quantum);
    ReadyQueue.move_next_node(accum_time);
  }
}

/*
5 100
p1 150
p2 80
p3 200
p4 350
p5 20
*/
