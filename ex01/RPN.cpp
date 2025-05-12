#include "RPN.hpp"

#include <list>
#include <stack>
#include <iostream>

RPN::RPN() {}
RPN::RPN(const RPN&) {}
RPN& RPN::operator =(const RPN&) { return *this; }
RPN::~RPN() {}

std::tuple<bool,int>	RPN::calculate(const std::string input) {
	std::stack<int,std::list<int>>	stack;

	for (const char& c : input) {
		switch (c) {
			case ' ': {
				continue;
			}
			case '+': {
				if (stack.size() < 2) {
					std::cerr << "Error: missing operand for binary operator" << std::endl;
					return {true, 0};
				}
				int a = stack.top();
				stack.pop();
				int b = stack.top();
				stack.pop();
				stack.push(a + b);
				break ;
			}
			case '-': {
				if (stack.size() < 2) {
					std::cerr << "Error: missing operand for binary operator" << std::endl;
					return {true, 0};
				}
				int a = stack.top();
				stack.pop();
				int b = stack.top();
				stack.pop();
				stack.push(a - b);
				break ;
			}
			case '*': {
				if (stack.size() < 2) {
					std::cerr << "Error: missing operand for binary operator" << std::endl;
					return {true, 0};
				}
				int a = stack.top();
				stack.pop();
				int b = stack.top();
				stack.pop();
				stack.push(a * b);
				break ;
			}
			case '/': {
				if (stack.size() < 2) {
					std::cerr << "Error: missing operand for binary operator" << std::endl;
					return {true, 0};
				}
				int a = stack.top();
				stack.pop();
				int b = stack.top();
				stack.pop();
				stack.push(a / b);
				break ;
			}
			default: {
				if (!std::isdigit(c)) {
					std::cerr << "Error: character is not a valid operand, space, or digit" << std::endl;
					return {true, 0};
				}
				stack.push( c - '0');
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
