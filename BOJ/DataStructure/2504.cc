// BOJ 2504
#include <iostream>
#include <string>
#include <sstream>
#include <stack>

class bracket_frame : public std::stack<int>
{
private:
  int value;

public:
  bracket_frame() : value(1) {}
  //~bracket_frame() { delete static_cast<std::stack<int> *>(this); }
  int &add_value(int n) { return value += n; }

  void unwind_stack(int n)
  {
    // value check
    int current_top = this->top();

    if (n != current_top)
    {
      throw std::exception();
    }

    // calculate
    value *= n;
    this->pop();
  }
  int get_value() { return value; }
};

std::stack<bracket_frame> frame_st;
bool open_flag; // true -> add, false -> multiply

void bracket_open(int value)
{
  if (!open_flag) // close -> open
  {
    frame_st.push(bracket_frame());
    open_flag = true;
  }
  frame_st.top().push(value);
}

void bracket_close(int value)
{
  try
  {

    if (frame_st.top().empty())
    {
      throw std::exception();
    }
    if (open_flag) // open -> close
    {
      open_flag = false;
    }

    frame_st.top().unwind_stack(value);

    if (frame_st.top().empty() && frame_st.size() > 1)
    {
      int temp_value = frame_st.top().get_value();
      frame_st.pop();
      frame_st.top().add_value(temp_value);
    }
  }
  catch (const std::exception &e)
  {
    throw e;
  }
}

int main()
{
  open_flag = true;
  frame_st.push(bracket_frame());

  // input
  std::string data;
  std::getline(std::cin, data);
  std::istringstream ss(data);

  // processing
  char temp;

  try
  {
    while (ss >> temp)
    {
      switch (temp)
      {
      case '(':
        bracket_open(2);
        break;
      case '[':
        bracket_open(3);
        break;
      case ')':
        bracket_close(2);
        break;
      case ']':
        bracket_close(3);
        break;
      default:
        perror("wrong input data.");
        abort();
        break;
      }
    }

    if (!frame_st.top().empty())
    {
      throw std::exception();
    }
  }
  catch (const std::exception &e)
  {
    std::cout << '0' << '\n';
    exit(0);
  }

  // normal output
  // calculating
  std::cout << frame_st.top().get_value() << std::endl;
}