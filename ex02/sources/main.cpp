/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:00:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/11/18 11:00:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <deque>
#include <iterator>
#include "../includes/PmergeMe.hpp"


/////////////////////////////////////////////////////////////////////////////
// Parser functions

template <typename Container>
bool isSorted(const Container& container)
{
	typename Container::const_iterator current = container.begin();
	typename Container::const_iterator next = container.begin();
	++next;

	while (next != container.end())
	{
		if (*current > *next)
		{
			std::cout << "Not sorted" << std::endl;
			return (false);
		}
		++current;
		++next;
	}
	std::cout << "Sorted" << std::endl;

	return (true);
}

bool checkDuplicates(const std::deque<int>& sequence)
{
	std::deque<int> seqSorted = sequence;
	std::sort(seqSorted.begin(), seqSorted.end());
	for (size_t i = 1; i < seqSorted.size(); i++)
	{
		if (seqSorted[i - 1] == seqSorted[i])
		{
			std::cerr << "Error: invalid input in sequence, duplicated: " << seqSorted[i] << std::endl;
			return (true);
		}
	}

	return (false);
}

bool validateSequence(int argc, char** argv, std::deque<int>& sequence)
{

	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		for (size_t j = 0; j < arg.size(); j++)
		{
			if (j == 0 && (arg[j] == '+' || arg[j] == '-' ))
				continue;
			if (!isdigit(arg[j]))
			{
				std::cerr << "Error: invalid input in sequence: " << arg << std::endl;
				return (false);
			}
		}
		
		int num = std::atoi(argv[i]);
		if (num < 0)
		{
			std::cerr << "Error: invalid input in sequence, negative: " << num << std::endl;
			return (false);
		}
		sequence.push_back(num);
	}
	if (checkDuplicates(sequence))
		return (false);

	return (true);
}


/////////////////////////////////////////////////////////////////////////////
// Mesure elapsed time functions

double measureSortTimeVector(std::vector<int> vec)
{
    const int iterations = 100;
    clock_t totalTime = 0;
    
    for (int i = 0; i < iterations; ++i)
    {
        std::vector<int> copy = vec;
        
		PmergeMe pmVec;
        clock_t start = clock();
        pmVec.sortVector(copy);
        clock_t end = clock();
        
        totalTime += (end - start);
		std::cout << "Time to process with std::vector: " << end - start << " us" << std::endl;
    }
    
    return (double)totalTime / iterations / CLOCKS_PER_SEC * 1000000;
}

double measureSortTimeDeque(std::deque<int> deq)
{
    const int iterations = 100;
    clock_t totalTime = 0;
    
    for (int i = 0; i < iterations; ++i)
    {
        std::deque<int> copy = deq;
        
		PmergeMe pmDeq;
        clock_t start = clock();
        pmDeq.sortDeque(copy);
        clock_t end = clock();
        
        totalTime += (end - start);
		std::cout << "Time to process with std::deque: " << end - start << " us" << std::endl;
    }
    
    return (double)totalTime / iterations / CLOCKS_PER_SEC * 1000000;
}


/////////////////////////////////////////////////////////////////////////////
// Main

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: needed a positive integer sequence." << std::endl;
		return (1);
	}

	std::deque<int> sequence;
	if (!validateSequence(argc, argv, sequence))
		return (1);
	// printContainer(sequence);

    std::vector<int> vec;
    std::deque<int> deq;
    
    for (int i = 1; i < argc; ++i)
    {
        int num = std::atoi(argv[i]);
        vec.push_back(num);
        deq.push_back(num);
    }
	std::vector<int> copyVec = vec;
	std::deque<int> copyDeq = deq;


	// Single vector process
    std::cout << "Before (Vector): ";
    printContainer(vec);
    
	PmergeMe pmVec;
    clock_t startVec = clock();
	pmVec.sortVector(vec);
    clock_t endVec = clock();
    double timeVec = (double)(endVec - startVec) / CLOCKS_PER_SEC * 1000000;
    
    std::cout << "After:           ";
    printContainer(vec);
    std::cout << "Time to process with std::vector: " << timeVec << " us" << std::endl;


	// Single deque process
    std::cout << "\nBefore (Deque):  ";
    printContainer(deq);

	PmergeMe pmDeq;
    clock_t start = clock();
	pmDeq.sortDeque(deq);
    clock_t end = clock();
    double timeDeq = (double)(end - start) / CLOCKS_PER_SEC * 1000000;
    
    std::cout << "After:           ";
    printContainer(deq);
    std::cout << "Time to process with std::deque: " << timeDeq << " us" << std::endl << std::endl;
	
	
	// Average time tests
	double totalSortTime = measureSortTimeVector(copyVec);
	std::cout << "Average time to process with std::vector: " << totalSortTime << " us" << std::endl << std::endl;

	double totalSortTimeDeq = measureSortTimeDeque(copyDeq);
	std::cout << "Average time to process with std::deque: " << totalSortTimeDeq << " us" << std::endl << std::endl;

	std::cout << "Average time to process with std::vector: " << totalSortTime << " us" << std::endl;
	std::cout << "Average time to process with std::deque: " << totalSortTimeDeq << " us" << std::endl;


	return (0);
}


/////////////////////////////////////////////////////////////////////////////
// Tests

// ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
// ./PmergeMe `shuf -i 1-100000 -n 5000 | tr "\n" " "`
// ./PmergeMe `shuf -i 1-100000 -n 50000 | tr "\n" " "`


/////////////////////////////////////////////////////////////////////////////
// Notes

// Resumen del algoritmo Ford-Johnson (Merge-Insert):
// 1 Emparejar → Dividir en pares y ordenar cada par
// 2 Ordenar recursivamente → Ordenar los elementos mayores
// 3 Construir cadena principal → Primer menor + mayores ordenados
// 4 Insertar con Jacobsthal → Insertar menores restantes en orden óptimo
// 5 Insertar straggler → Añadir elemento impar si existe
// Este algoritmo minimiza comparaciones usando la secuencia de Jacobsthal para determinar el orden óptimo de inserción.

// típicamente vector es 10-30% más rápido que deque para este algoritmo (por mejor cache locality)
