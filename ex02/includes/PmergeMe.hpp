/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:00:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/11/18 11:00:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>
# include <ostream>

class PmergeMe
{
	private:
		std::vector<size_t> generateJacobsthalSequence(size_t n);

		size_t binarySearch(std::vector<int>& vec, int value, size_t end);
		void insertPendingVector(std::vector<int>& mainChain, const std::vector<int>& pending);
		void createPairsVector(std::vector<int>& vec, std::vector<std::pair<int, int> >& pairs, int& straggler);
		void fordJohnsonVector(std::vector<int>& vec);

		size_t binarySearch(std::deque<int>& deq, int value, size_t end);
		void insertPendingDeque(std::deque<int>& mainChain, const std::deque<int>& pending);
		void createPairsDeque(std::deque<int>& deq, std::vector<std::pair<int, int> >& pairs, int& straggler);
		void fordJohnsonDeque(std::deque<int>& deq);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe& operator=(const PmergeMe&);
		~PmergeMe();

		void sortVector(std::vector<int>& vec);
		void sortDeque(std::deque<int>& deq);
};

template <typename Container>
void printContainer(const Container& container)
{
	for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

#endif