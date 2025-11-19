/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 20:00:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/11/14 20:00:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../includes/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _container(other._container) {}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_container = other._container;
	return (*this);
}
BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::addRegister(Data& bitcoinExchangeRegister)
{
	_container.push_back(bitcoinExchangeRegister);
}

void BitcoinExchange::printBitcoinExchange() const
{
	for (unsigned int i = 0; i < _container.size(); i++)
	{
		char buffer[11];
		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &_container[i].date);
		
		std::cout << buffer << ", " << _container[i].value << std::endl;
	}
	std::cout << std::endl;
}

double BitcoinExchange::resultBitcoinExchange(Data& bitcoinExchangeRegister)
{
	std::vector<Data>::iterator it = findLowerClosestDate(_container, bitcoinExchangeRegister.date);
	if (it != _container.end())
	{
		double result = it->value * bitcoinExchangeRegister.value;
		return result;
	}
	std::cerr << "Error: date not in database range" << std::endl;

	return (-1.0);
}

int compareTm(const std::string& tm1, const std::string& tm2)
{
	if (tm1.tm_year != tm2.tm_year)
		return tm1.tm_year - tm2.tm_year;
	if (tm1.tm_mon != tm2.tm_mon)
		return tm1.tm_mon - tm2.tm_mon;
	return tm1.tm_mday - tm2.tm_mday;
}
