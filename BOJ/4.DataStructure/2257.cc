// Solved.
#include <iostream>
#include <stack>
#include <sstream>

// 뒤에 붙는 숫자는 곱셈, 그 외는 모두 덧셈을 뜻한다.
// 일단 스택에 전부 숫자로 변환해서 집어넣다가 숫자를 만나면 pop해서 곱한다.
// 괄호를 만나면 덧셈을 누적하다가 숫자를 만나면 pop해서 곱한다.
// 이후

bool calChemicalExp(std::stack<int> &data_stack, std::istringstream &ss)
{
  char temp_char;
  int accum_counter = 0;

  ss >> temp_char;
  while (ss)
  {
    switch (temp_char)
    {
    case 'C':
      data_stack.push(12);
      accum_counter++;
      break;
    case 'H':
      data_stack.push(1);
      accum_counter++;
      break;
    case 'O':
      data_stack.push(16);
      accum_counter++;
      break;
    case '(': // recurse
      accum_counter++;
      calChemicalExp(data_stack, ss);

      break;
    case ')': // return
    {
      int temp_value = 0;
      for (int i = 0; i < accum_counter; i++)
      {
        temp_value += data_stack.top();
        data_stack.pop();
      }
      data_stack.push(temp_value);

      return true;

      break;
    }
    default: // input was a number
      data_stack.top() *= temp_char - '0';
      break;
    }

    // read next char
    ss >> temp_char;
  }

  return false;
}

int main()
{
  char temp_char;
  int accum_counter = 0;

  std::string stream_buffer;
  std::getline(std::cin, stream_buffer);

  std::istringstream ss(stream_buffer);

  std::stack<int> data_stack;

  // stack processing
  calChemicalExp(data_stack, ss);

  // calculate the result
  int result = 0;
  while (!data_stack.empty())
  {
    result += data_stack.top();
    data_stack.pop();
  }

  std::cout << result << std::endl;
}