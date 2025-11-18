/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:00:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/11/17 19:00:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../includes/RPN.hpp"

bool inputFileProcess(const std::string& expression, RPN& stackRPN)
{
	if (expression.length() == 0)
		return (false);

	size_t i = 0;
	while (expression[i])
	{
		if (expression[i] == ' ')
		{
			i++;
			continue;
		}
		if (isdigit(expression[i]))
		{
			stackRPN.pushOperand(expression[i] - 48);
			i++;
			if (isdigit(expression[i]))
				return (false);
			continue;
		}
		if (stackRPN.operate(expression[i]))
		{
			i++;
			continue;
		}
		else
			return (false);
		i++;
	}

	return (true);
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: could not process expression" << std::endl;
		return (1);
	}

	RPN stackRPN = RPN();
	if (!inputFileProcess(argv[1], stackRPN))
	{
		std::cerr << "Error: expression wasn't processed." << std::endl;
		return (1);
	}

	if (stackRPN.getSize() != 1)
	{
		std::cerr << "Error: invalid expression" << std::endl;
		return (1);
	}
	std::cout << stackRPN.getValue() << std::endl;

	return (0);
}