/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:00:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/11/18 11:00:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other) : _container(other._container) {}
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
		_container = other._container;
	return (*this);
}
PmergeMe::~PmergeMe() {}


size_t PmergeMe::binarySearch(std::vector<int>& vec, int value, size_t end)
{
	size_t left = 0;
	size_t right = end;

	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (vec[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}

	return (left);
}

std::vector<size_t> PmergeMe::generateJacobsthalSequence(size_t n)
{
	std::vector<size_t> jacobsthal;
	if (n == 0)
		return (jacobsthal);

	size_t j0 = 0;
	size_t j1 = 1;
	while (j1 < n)
	{
		jacobsthal.push_back(j1);
		size_t next = j1 + 2 * j0;
		if (next > n)
			break;
		j0 = j1;
		j1 = next;
	}

	if (jacobsthal.empty() || jacobsthal.back() < n)
		jacobsthal.push_back(n);

	std::vector<size_t> insertionOrder;
	size_t prevJacob = 0;
	for (size_t i = 0; i < jacobsthal.size(); ++i)
	{
		size_t currentJacob = jacobsthal[i];
		for (size_t j = currentJacob; j > prevJacob; --j)
				insertionOrder.push_back(j - 1);
		prevJacob = currentJacob;
	}
	std::cout << "insertionOrder: ";
	printContainer(insertionOrder);

	return (insertionOrder);
}

void PmergeMe::insertPendingVector(std::vector<int>& mainChain, const std::vector<int>& pending)
{
	if (pending.empty())
		return;
	
	std::vector<size_t> insertionOrder = generateJacobsthalSequence(pending.size());
	for (size_t i = 0; i < insertionOrder.size(); i++)
	{
		size_t idx = insertionOrder[i];
		if (idx < pending.size())
		{
			int value = pending[idx];
			size_t pos = binarySearch(mainChain, value, mainChain.size());
			mainChain.insert(mainChain.begin() + pos, value);
		}
	}
	std::cout << "mainChain insertPendingVector: ";
	printContainer(mainChain);
}

void PmergeMe::createPairsVector(std::vector<int>& vec, std::vector<std::pair<int, int> >& pairs, int& straggler)
{
	size_t i = 0;
	while (i + 1 < vec.size())
	{
		int a = vec[i];
		int b = vec[i + 1];
		if (a > b)
			pairs.push_back(std::make_pair(a, b));
		else
			pairs.push_back(std::make_pair(b, a));

		i += 2;
	}

	if (i < vec.size())
		straggler = vec[i];

	std::cout << "pairs: ( ";
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		std::cout << "(" << pairs[i].first << ", " << pairs[i].second << ") ";
	}
	std::cout << ")" << " straggler: " << straggler << std::endl;
	
}

void PmergeMe::fordJohnsonVector(std::vector<int>& vec)
{
	if (vec.size() <= 1)
		return;
	
	std::vector<std::pair<int, int> > pairs;
	int straggler = -1;
	createPairsVector(vec, pairs, straggler);
	std::vector<int> larger;
	std::vector<int> smaller;
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		larger.push_back(pairs[i].first);
		smaller.push_back(pairs[i].second);
	}
	std::cout << "larger pre: ";
	printContainer(larger);
	std::cout << "smaller: ";
	printContainer(smaller);

	if (larger.size() > 1)
		fordJohnsonVector(larger);
	std::cout << "larger post: ";
	printContainer(larger);

	std::vector<int> mainChain;
	if (!smaller.empty())
		mainChain.push_back(smaller[0]);

	for (size_t i = 0; i < larger.size(); ++i)
		mainChain.push_back(larger[i]);
	std::cout << "mainChain: ";
	printContainer(mainChain);
	
	std::vector<int> pending;
	for (size_t i = 1; i < smaller.size(); ++i)
		pending.push_back(smaller[i]);
	std::cout << "pending: ";
	printContainer(pending);
	
	insertPendingVector(mainChain, pending);

	if (straggler != -1)
	{
		size_t pos = binarySearch(mainChain, straggler, mainChain.size());
		mainChain.insert(mainChain.begin() + pos, straggler);
	}

	vec = mainChain;
	std::cout << "vec fordJohnsonVector: ";
	printContainer(vec);

}

void PmergeMe::sortVector(std::vector<int>& vec)
{
	if (vec.size() <= 1)
		return;
	fordJohnsonVector(vec);
}