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
#include <algorithm>
#include <cctype>
#include <ctime>
#include <cstring>
#include "../includes/BitcoinExchange.hpp"

std::tm stringToTm(const std::string& dateStr)
{
	std::tm tm;
	std::memset(&tm, 0, sizeof(tm));
	
	std::stringstream ss(dateStr);
	char dash;
	ss >> tm.tm_year >> dash >> tm.tm_mon >> dash >> tm.tm_mday;
	
	tm.tm_year -= 1900;
	tm.tm_mon -= 1;
	
	return (tm);
}

std::string trim(const std::string& str)
{
	size_t first = str.find_first_not_of(" \t\n\r");
	if (first == std::string::npos)
		return ("");
	size_t last = str.find_last_not_of(" \t\n\r");
	return (str.substr(first, last - first + 1));
}

bool isNumber(const std::string& str)
{
	if (str.empty())
		return false;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}

int stringToInt(const std::string& str)
{
	std::stringstream ss(str);
	int result;
	ss >> result;
	if (ss.fail())
		return -1;
	return result;
}

std::string checkDate(const std::string& checkedDate)
{
	if (checkedDate == "date")
		return ("");
	size_t checkedDateSize = checkedDate.size();
	size_t found1 = checkedDate.find("-", 0);
	size_t found2 = checkedDate.find("-", found1 + 1);
	if (found1 != 4 || found2 != 7 || checkedDateSize != 10)
	{
		std::cerr << "Error: bad date input format => " << checkedDate << std::endl;
		return ("");
	}
	
	std::string yearStr = checkedDate.substr(0, 4);
	std::string monthStr = checkedDate.substr(5, 2);
	std::string dayStr = checkedDate.substr(8, 2);
	if (!isNumber(yearStr) || !isNumber(monthStr) || !isNumber(dayStr))
	{
		std::cerr << "Error: bad date input format => " << checkedDate << std::endl;
		return ("");
	}

	int year = stringToInt(yearStr);
	int month = stringToInt(monthStr);
	int day = stringToInt(dayStr);
	if (year < 2000 || year > 2050 || month < 1 || month > 12 || day < 1 || day > 31)
	{
		std::cerr << "Error: bad date input format => " << checkedDate << std::endl;
		return ("");
	}

	return (checkedDate);
}

double checkValue(const std::string& toCheckValue)
{
	std::stringstream ss(toCheckValue);
	double checkedValue;
	ss >> checkedValue;
	if (ss.fail())
	{
		std::cerr << "Error: bad value input => " << toCheckValue << std::endl;
		return (-1);
	}
	std::string remaining;
	ss >> remaining;
	if (!remaining.empty())
	{
		std::cerr << "Error: bad value input => " << toCheckValue << std::endl;
		return (-1);
	}
	if (checkedValue < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (-1);
	}
	else if (checkedValue > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return (-1);
	}
	
	return (checkedValue);
}

Data	lineProcess(const std::string &line)
{
	Data bitcoinExchangeRegister;

	std::memset(&bitcoinExchangeRegister.date, 0, sizeof(std::tm));
	bitcoinExchangeRegister.date.tm_year = -1;
	bitcoinExchangeRegister.value = -1;

	if (line.empty())
		return (bitcoinExchangeRegister);

	size_t lineSize = line.size();
	size_t found = line.find("|", 0);

	if (found == std::string::npos)
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return (bitcoinExchangeRegister);
	}
	
	std::string checkedDate = checkDate(trim(line.substr(0, found)));
	if (checkedDate != "")
		bitcoinExchangeRegister.date = stringToTm(checkedDate);

	double checkedValue = checkValue(line.substr(found + 1, lineSize - (found + 1)));
	if (checkedValue != -1)
		bitcoinExchangeRegister.value = checkedValue;

	return (bitcoinExchangeRegister);
}

bool	inputFileProcess(const std::string& inputFileName, BitcoinExchange& bitcoinExchangeData)
{
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
		if (bitcoinExchangeRegister.date.tm_year != -1 && bitcoinExchangeRegister.value != -1)
		{
			char buffer[11];  // YYYY-MM-DD + '\0'
			std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &bitcoinExchangeRegister.date);
			std::cout << buffer<< "=> ";
			std::cout << bitcoinExchangeRegister.value << " = ";
			std::cout << bitcoinExchangeData.resultBitcoinExchange(bitcoinExchangeRegister);
			std::cout << std::endl;
		}	
	}

	inputFile.close();

	return (true);
}

Data	dataBaseLineProcess(const std::string &line)
{
	Data bitcoinExchangeRegister;

	std::memset(&bitcoinExchangeRegister.date, 0, sizeof(std::tm));
	bitcoinExchangeRegister.date.tm_year = -1;
	bitcoinExchangeRegister.value = -1;

	if (line.empty())
		return (bitcoinExchangeRegister);

	size_t lineSize = line.size();
	size_t found = line.find(",", 0);

	if (found != std::string::npos)
	{	
		bitcoinExchangeRegister.date = stringToTm(line.substr(0, found));
		std::stringstream ss(line.substr(found + 1, lineSize - (found + 1)));
		ss >> bitcoinExchangeRegister.value;
	}

	return (bitcoinExchangeRegister);
}


bool	dataBaseFileProcess(const std::string& inputFileName, BitcoinExchange& bitcoinExchangeData)
{
	Data bitcoinExchangeRegister;

	std::ifstream inputFile(inputFileName.c_str());
	if (!inputFile.is_open())
	{
		std::cerr << "Error: could not open file " << inputFileName << " to read." << std::endl;
		return (false);
	}

	std::string line;
	while (std::getline(inputFile, line))
	{
		bitcoinExchangeRegister = dataBaseLineProcess(line);
		if (bitcoinExchangeRegister.date.tm_year != -1)
			bitcoinExchangeData.addRegister(bitcoinExchangeRegister);
	}

	inputFile.close();

	return (true);
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file" << std::endl;
		return (1);
	}

	std::string	inputFileName = argv[1];
	if (inputFileName.empty())
	{
		std::cerr << "Error: input file cannot be empty." << std::endl;
		return (1);
	}

	BitcoinExchange bitcoinExchangeData = BitcoinExchange();
	std::cout << std::fixed << std::setprecision(2);

	if (!dataBaseFileProcess("data.csv", bitcoinExchangeData))
	{
		std::cerr << "Error: database file wasn't included." << std::endl;
		return (1);
	}
	// bitcoinExchangeData.printBitcoinExchange();

	if (!inputFileProcess(inputFileName, bitcoinExchangeData))
	{
		std::cerr << "Error: input file wasn't processed." << std::endl;
		return (1);
	}

	return (0);
}