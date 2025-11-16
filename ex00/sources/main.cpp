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
#include "../includes/BitcoinExchange.hpp"

Data	lineProcess(const std::string &line)
{
	Data bitcoinExchangeRegister;

	// if (line.empty())
	// 	return (NULL);

	size_t lineSize = line.size();
	size_t found = line.find(",", 0);

	if (found != 0)
	{	
		bitcoinExchangeRegister.date = line.substr(0, found);
		// bitcoinExchangeRegister.value = std::stof(line.substr(found + 1, lineSize - found + 1 ));
		std::stringstream ss(line.substr(found + 1, lineSize - found));
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
		bitcoinExchangeData.addRegister(bitcoinExchangeRegister);
	}
	bitcoinExchangeData.printBitcoinExchange();

	// bitcoinExchangeRegister.date = "1969-07-13";
	// bitcoinExchangeRegister.value = 56;

	// bitcoinExchangeData.addRegister(bitcoinExchangeRegister);
	// bitcoinExchangeData.printBitcoinExchange();

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
	if (!fileProcess(inputFileName))
	{
		std::cerr << "Error: file wasn't processed." << std::endl;
		return (1);
	}

	return (0);
}