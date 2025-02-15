// Reverse Polish notation.

#include <iostream>
#include <sstream>
#include "MyStack.h"

int main()
{
  // set data structure
  std::string token, buffer;
  MyStack<float> stack;
  float l_var, r_var;

  std::getline(std::cin, buffer);
  std::istringstream ss(buffer);

  while (ss >> token)
  {
    // handling input
    // if the input string is a operator, pop and operate
    switch (token.at(0))
    {
    case '+':
      l_var = stack.top();
      stack.pop();
      r_var = stack.top();
      stack.pop();
      stack.push(l_var + r_var);
      break;
    case '-':
      l_var = stack.top();
      stack.pop();
      r_var = stack.top();
      stack.pop();
      stack.push(l_var - r_var);
      break;
    case '*':
      l_var = stack.top();
      stack.pop();
      r_var = stack.top();
      stack.pop();
      stack.push(l_var * r_var);
      break;
    case '/':
      l_var = stack.top();
      stack.pop();
      r_var = stack.top();
      stack.pop();
      stack.push(l_var / r_var);
      break;
    default: // else, put it in the stack(push)
      stack.push(std::stof(token));
      break;
    }
  }

  // output
  if (stack.size() == 1)
  {
    std::cout << stack.top() << std::endl;
    return 0;
  }
  else
  {
    std::cout << "Stack Arithmatic has an error." << std::endl;
    return -1;
  }
}