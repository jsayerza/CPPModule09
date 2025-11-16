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
		std::cout << _container[i].date << ", " << _container[i].value << std::endl;
	std::cout << std::endl;
}