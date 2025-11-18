/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:00:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/11/17 19:00:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../includes/RPN.hpp"

RPN::RPN() {}
RPN::RPN(const RPN& other) : _container(other._container) {}
RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		_container = other._container;
	return (*this);
}
RPN::~RPN() {}

void RPN::pushOperand(const double operand)
{
	_container.push(operand);
}

double RPN::getValue()
{
	return (_container.top());
}

int RPN::getSize()
{
	return (_container.size());
}


bool RPN::operate(const char& operatorRPN)
{
	double op1, op2;

	if (_container.size() < 2)
		return (false);
	if (operatorRPN != '+' && operatorRPN != '-' && operatorRPN != '*' && operatorRPN != '/')
		return (false);

	op2 = _container.top();
	_container.pop();
	op1 = _container.top();
	_container.pop();

	switch (operatorRPN)
	{
	case '+':
		_container.push(op1 + op2);
		break;

	case '-':
		_container.push(op1 - op2);
		break;

	case '*':
		_container.push(op1 * op2);
		break;

	case '/':
		if (op2 == 0)
		{
			std::cerr << "Error: division by 0" << std::endl;
			return (false);
			break;
		}	
		_container.push(op1 / op2);
		break;
		
	default:
		return (false);
		break;
	}

	op2 = _container.top();

	return (true);
}
