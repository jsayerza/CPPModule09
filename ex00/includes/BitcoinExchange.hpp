/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 20:00:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/11/14 20:00:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <vector>
# include <string>
# include <ctime>

struct Data
{
	std::tm date;
	double value;
};

class BitcoinExchange
{
	private:
		std::vector<Data> _container;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		void addRegister(Data& bitcoinExchangeRegister);
		void printBitcoinExchange() const;

		double resultBitcoinExchange(Data& bitcoinExchangeRegister);
};

int compareTm(const std::tm& tm1, const std::tm& tm2);

template <typename T>
typename T::iterator findLowerClosestDate(T& container, const std::tm& dateToFind)
{
	if (container.empty())
		return container.end();
	
	typename T::iterator it = container.end();
	--it;
	while (true)
	{
		if (compareTm(it->date, dateToFind) <= 0)
			return (it);
		if (it == container.begin())
			break;
		--it;
	}
	
	return (container.end());
}

#endif