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
		std::deque<double> _container;

		size_t binarySearch(std::vector<int>& vec, int value, size_t end);
		std::vector<size_t> generateJacobsthalSequence(size_t n);
		void insertPendingVector(std::vector<int>& mainChain, const std::vector<int>& pending);
		void createPairsVector(std::vector<int>& vec, std::vector<std::pair<int, int> >& pairs, int& straggler);
		void fordJohnsonVector(std::vector<int>& vec);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		void sortVector(std::vector<int>& vec);
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