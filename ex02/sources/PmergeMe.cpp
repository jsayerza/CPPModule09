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
PmergeMe::PmergeMe(const PmergeMe&) {}
PmergeMe& PmergeMe::operator=(const PmergeMe&) { return (*this); }
PmergeMe::~PmergeMe() {}

///////////////////////////////////////////////////////////////////
// Common functions

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
	// std::cout << "insertionOrder: ";
	// printContainer(insertionOrder);

	return (insertionOrder);
}

////////////////////////////////////////////////////////////////////
// Vector functions

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
	// std::cout << "mainChain insertPendingVector: ";
	// printContainer(mainChain);
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

	// std::cout << "pairs: ( ";
	// for (size_t i = 0; i < pairs.size(); ++i)
	// {
	// 	std::cout << "(" << pairs[i].first << ", " << pairs[i].second << ") ";
	// }
	// std::cout << ")" << " straggler: " << straggler << std::endl;
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
	// std::cout << "larger pre: ";
	// printContainer(larger);
	// std::cout << "smaller: ";
	// printContainer(smaller);

	if (larger.size() > 1)
		fordJohnsonVector(larger);
	// std::cout << "larger post: ";
	// printContainer(larger);

	std::vector<int> mainChain;
	if (!smaller.empty())
		mainChain.push_back(smaller[0]);

	for (size_t i = 0; i < larger.size(); ++i)
		mainChain.push_back(larger[i]);
	// std::cout << "mainChain: ";
	// printContainer(mainChain);
	
	std::vector<int> pending;
	for (size_t i = 1; i < smaller.size(); ++i)
		pending.push_back(smaller[i]);
	// std::cout << "pending: ";
	// printContainer(pending);
	
	insertPendingVector(mainChain, pending);

	if (straggler != -1)
	{
		size_t pos = binarySearch(mainChain, straggler, mainChain.size());
		mainChain.insert(mainChain.begin() + pos, straggler);
	}

	vec = mainChain;
	// std::cout << "vec fordJohnsonVector: ";
	// printContainer(vec);
}

void PmergeMe::sortVector(std::vector<int>& vec)
{
	if (vec.size() <= 1)
		return;
	fordJohnsonVector(vec);
}

//////////////////////////////////////////////////////////////////////////
// Deque functions

size_t PmergeMe::binarySearch(std::deque<int>& deq, int value, size_t end)
{
	size_t left = 0;
	size_t right = end;

	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (deq[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}

	return (left);
}

void PmergeMe::insertPendingDeque(std::deque<int>& mainChain, const std::deque<int>& pending)
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
	// std::cout << "mainChain insertPendingDeque: ";
	// printContainer(mainChain);
}

void PmergeMe::createPairsDeque(std::deque<int>& deq, std::vector<std::pair<int, int> >& pairs, int& straggler)
{
	size_t i = 0;
	while (i + 1 < deq.size())
	{
		int a = deq[i];
		int b = deq[i + 1];
		if (a > b)
			pairs.push_back(std::make_pair(a, b));
		else
			pairs.push_back(std::make_pair(b, a));

		i += 2;
	}

	if (i < deq.size())
		straggler = deq[i];

	// std::cout << "pairs: ( ";
	// for (size_t i = 0; i < pairs.size(); ++i)
	// {
	// 	std::cout << "(" << pairs[i].first << ", " << pairs[i].second << ") ";
	// }
	// std::cout << ")" << " straggler: " << straggler << std::endl;
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& deq)
{
	if (deq.size() <= 1)
		return;
	
	std::vector<std::pair<int, int> > pairs;
	int straggler = -1;
	createPairsDeque(deq, pairs, straggler);
	std::deque<int> larger;
	std::deque<int> smaller;
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		larger.push_back(pairs[i].first);
		smaller.push_back(pairs[i].second);
	}
	// std::cout << "larger pre: ";
	// printContainer(larger);
	// std::cout << "smaller: ";
	// printContainer(smaller);

	if (larger.size() > 1)
		fordJohnsonDeque(larger);
	// std::cout << "larger post: ";
	// printContainer(larger);

	std::deque<int> mainChain;
	if (!smaller.empty())
		mainChain.push_back(smaller[0]);

	for (size_t i = 0; i < larger.size(); ++i)
		mainChain.push_back(larger[i]);
	// std::cout << "mainChain: ";
	// printContainer(mainChain);
	
	std::deque<int> pending;
	for (size_t i = 1; i < smaller.size(); ++i)
		pending.push_back(smaller[i]);
	// std::cout << "pending: ";
	// printContainer(pending);
	
	insertPendingDeque(mainChain, pending);

	if (straggler != -1)
	{
		size_t pos = binarySearch(mainChain, straggler, mainChain.size());
		mainChain.insert(mainChain.begin() + pos, straggler);
	}

	deq = mainChain;
	// std::cout << "deq fordJohnsonDeque: ";
	// printContainer(deq);
}

void PmergeMe::sortDeque(std::deque<int>& deq)
{
	if (deq.size() <= 1)
		return;
	fordJohnsonDeque(deq);
}
