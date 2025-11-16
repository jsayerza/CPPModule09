/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 20:00:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/11/14 20:00:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "../includes/BitcoinExchange.hpp"

Data	lineProcess(const std::string &line)
{
	Data bitcoinExchangeRegister;

	bitcoinExchangeRegister.date = "";
	bitcoinExchangeRegister.value = -1;

	if (line.empty())
		return (bitcoinExchangeRegister);

	size_t lineSize = line.size();
	size_t found = line.find(",", 0);

	if (found != 0)
	{	
		bitcoinExchangeRegister.date = line.substr(0, found);
		std::stringstream ss(line.substr(found + 1, lineSize - (found + 1)));
		// std::cout << "lineSize: " << lineSize << "  found: " << found << std::endl;
		// std::cout << "found + 1: " << found + 1 << "  lineSize - (found + 1): " << lineSize - (found + 1) << std::endl;
		// std::cout << "ss: " << ss.str() << std::endl;
		ss >> bitcoinExchangeRegister.value;
	}

	return (bitcoinExchangeRegister);
}


bool	fileProcess(const std::string& inputFileName)
{
	BitcoinExchange bitcoinExchangeData = BitcoinExchange();
	Data bitcoinExchangeRegister;

	std::ifstream inputFile(inputFileName.c_str());
	if (!inputFile.is_open())
	{
		std::cerr << "Error: unable to open file " << inputFileName << " to read." << std::endl;
		return (false);
	}

	std::string line;
	while (std::getline(inputFile, line))
	{
		bitcoinExchangeRegister = lineProcess(line);
		if (bitcoinExchangeRegister.date != "")
			bitcoinExchangeData.addRegister(bitcoinExchangeRegister);
	}
	bitcoinExchangeData.printBitcoinExchange();

	inputFile.close();

	return (true);
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./btc {file}" << std::endl;
		return (1);
	}

	std::string	inputFileName = argv[1];
	if (inputFileName.empty())
	{
		std::cerr << "Error: input file cannot be empty." << std::endl;
		return (1);
	}

	std::cout << std::fixed << std::setprecision(2);

	if (!fileProcess(inputFileName))
	{
		std::cerr << "Error: file wasn't processed." << std::endl;
		return (1);
	}

	return (0);
}