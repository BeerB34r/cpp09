#include "RPN.hpp"

#include <list>
#include <stack>
#include <iostream>

static	bool	binary_op(std::stack<int,std::list<int>> &stack, int (*op)(int, int))
{
	if (stack.size() < 2) {
		std::cerr << "Error: missing operand for binary operator" << std::endl;
		return true;
	}
	int a = stack.top();
	stack.pop();
	int b = stack.top();
	stack.pop();
	try {
		stack.push(op(b,a));
		return false;
	} catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
		return true;
	}
}

std::tuple<bool,int>	RPN::calculate(const std::string input) {
	std::stack<int,std::list<int>>	stack;

	for (const char& c : input) {
		switch (c) {
			case ' ': {
				continue;
			}
			case '+': {
				if (binary_op(stack, [](int a, int b){ return a + b; }))
					return {true, 0};
				break ;
			}
			case '-': {
				if (binary_op(stack, [](int a, int b){ return a - b; }))
					return {true, 0};
				break ;
			}
			case '*': {
				if (binary_op(stack, [](int a, int b){ return a * b; }))
					return {true, 0};
				break ;
			}
			case '/': {
				if (binary_op(stack, [](int a, int b){
						if (b == 0) throw std::range_error("Error: division ill defined with divisor == 0");
						return a / b;
					}))
					return {true, 0};
				break ;
			}
			default: {
				if (!std::isdigit(c)) {
					std::cerr << "Error: character is not a valid operand, space, or digit" << std::endl;
					return {true, 0};
				}
				stack.push(c - '0');
			}
		}
	}
	if (stack.size() < 1) {
		std::cerr << "Error: stack is empty after all operations completed" << std::endl;
		return {true, 0};
	}
	if (stack.size() != 1) {
		std::clog << "Warning: excess elements in stack, only top element will be displayed" << std::endl;
	}
	return {false, stack.top()};
}
