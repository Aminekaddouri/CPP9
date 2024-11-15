#include "PmergeMe.hpp"
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <deque>
#include <iostream>
#include <ctime>

PmergeMe::PmergeMe(const std::vector<int>& seq) : sequence(seq) {}

void PmergeMe::sortWithVector()
{
    clock_t start = clock();
    std::vector<int> seqCopy = sequence;
    mergeInsertSort(seqCopy);
    clock_t end = clock();
    displaySequence(seqCopy, "After:");
    displayTime(static_cast<double>(end - start) / CLOCKS_PER_SEC * 1e6, "std::vector");
}

void PmergeMe::sortWithDeque()
{
    clock_t start = clock();
    std::deque<int> seqCopy(sequence.begin(), sequence.end());
    mergeInsertSort(seqCopy);
    clock_t end = clock();
    displaySequence(seqCopy, "After:");
    displayTime(static_cast<double>(end - start) / CLOCKS_PER_SEC * 1e6, "std::deque");
}

void PmergeMe::displaySequence(const std::vector<int>& seq, const std::string& msg)
{
    std::cout << msg << " ";
    for (size_t i = 0; i < seq.size(); i++)
        std::cout << seq[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::displaySequence(const std::deque<int>& seq, const std::string& msg)
{
    std::cout << msg << " ";
    for (size_t i = 0; i < seq.size(); i++)
        std::cout << seq[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::displayTime(double time, const std::string& containerType)
{
    std::cout << "Time to process with " << containerType << ": " << time << " us" << std::endl;
}

std::vector<int> PmergeMe::jacobsthalSequence(int n)
{
    std::vector<int> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    // Generate values until the next Jacobsthal number would exceed n
    while (true)
    {
        int next = jacobsthal.back() + 2 * jacobsthal[jacobsthal.size() - 2];
        jacobsthal.push_back(next);
        if (next > n)
            break;  // Stop if the next number exceeds n
    }

    return jacobsthal;
}

// Comparator function for sorting pairs by the larger element (first in pair)
bool comparePairs(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
    return (a.first < b.first);
}

int PmergeMe::returnIndexVector(std::vector<int> &v, int value){
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i] >= value && v[i-1] && v[i-1] < value)
        {
            return (i + 1);
        }
    }
    return -1;
}

std::vector<unsigned long> PmergeMe::jacobIndexGeneratorVector(std::vector<int> &jacobsthals, int size){
    // std::cout << "jacobsthals" << std::endl;
    // for (size_t i = 0; i < jacobsthals.size(); i++)
    //     std::cout << jacobsthals[i] << " ";
    // std::cout << std::endl;
    std::vector<unsigned long> jacobsthals_indexed;
    int jacob = 0;
    for (size_t i = 0; i < jacobsthals.size(); i++)
    {
        jacob = jacobsthals[i];
        if (jacob <= size)
            jacobsthals_indexed.push_back(jacob);
        while (jacob > 0 && jacobsthals[i] != 1 && std::find(jacobsthals_indexed.begin(), jacobsthals_indexed.end(), --jacob) == jacobsthals_indexed.end())
        {
            if (jacob > size)
            {
                continue;
            }
            jacobsthals_indexed.push_back(jacob);
        }
    }
    // remove one 1 from the beginning of the sequence
    jacobsthals_indexed.erase(jacobsthals_indexed.begin());
    return jacobsthals_indexed;
}

int PmergeMe::Jacobsthal(int n)
{
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    return Jacobsthal(n - 1) + 2 * Jacobsthal(n - 2);
}

template <typename T>
void PmergeMe::mergeInsertSort(T& seq)
{
    if (seq.size() < 2)
        return ;

    // Step 1: Pair elements and sort each pair
    std::vector<std::pair<int, int> > pairs;
    // std::cout 
    int struggle = (seq.size() % 2 != 0) ? seq.back() : -1;
    if (struggle != -1)
        seq.pop_back();
    for (size_t i = 0; i < seq.size(); i += 2)
    {
        if (seq[i] > seq[i + 1])
            pairs.push_back(std::make_pair(seq[i], seq[i + 1]));
        else
            pairs.push_back(std::make_pair(seq[i + 1], seq[i]));
    }
    // handle odd element if it exist (the "struggle" element)

    // Step 2: Sort pairs by the larger element (first in pair)
    std::sort(pairs.begin(), pairs.end(), comparePairs);

    // Step 3: Separate into B and S sequences
    T L; // Sorted larger elements
    T S; // Unsorted smaller elements
    for (size_t i = 0; i < pairs.size(); i++)
    {
        L.push_back(pairs[i].first);
        S.push_back(pairs[i].second);
    }

    // std::cout << "Sorted larger elements" << std::endl;
    // for (size_t i = 0; i < L.size(); i++)
    //     std::cout << L[i] << " ";
    // std::cout << std::endl;
    // std::cout << "Unsorted smaller elements" << std::endl;
    // for (size_t i = 0; i < S.size(); i++)
    //     std::cout << S[i] << " ";
    // std::cout << std::endl;

    // Step 4: Insert elements from S into B using Ford-Johnson (Jacobsthal order)
    if(S.size() >= 2){       
        std::vector<int> jacobsthals;
        std::vector<unsigned long> jacobsthals_indexed;
        unsigned long jacob = 0;
        for (size_t i = 2; i < S.size() + L.size(); i++)
        {
            jacob = Jacobsthal(i);
            // std::cout << "jacob = " << jacob << std::endl;
            if (jacob > S.size())
            {
                jacobsthals.push_back(jacob);
                break;
            }
            jacobsthals.push_back(jacob);
        }
        jacobsthals_indexed = jacobIndexGeneratorVector(jacobsthals, S.size());
        // std::cout << "jacobsthals_indexed = " << jacobsthals_indexed.size()<< std::endl;
        // for (size_t i = 0; i < jacobsthals_indexed.size(); i++)
        //     std::cout << jacobsthals_indexed[i] << " ";
        // std::cout << std::endl;

        //step four
        L.insert(L.begin(), S[0]);

        //step five
        int last_size = 0;
        for (size_t i = 0; i < jacobsthals_indexed.size(); i++)
        {
            if (jacobsthals_indexed[i] <= S.size())
            {
                // std::cout << "returnIndexVector = " << returnIndexVector(jacobsthals,jacobsthals_indexed[i]) << std::endl;
                if (pow(2, returnIndexVector(jacobsthals,jacobsthals_indexed[i])) - 1 > L.size())
                    last_size = L.size();
                else
                    last_size = pow(2, returnIndexVector(jacobsthals,jacobsthals_indexed[i])) - 1;
                // std::cout << "last_size = " << last_size << std::endl;
                L.insert(std::lower_bound(L.begin(), L.begin() + last_size, S[jacobsthals_indexed[i] - 1]), S[jacobsthals_indexed[i] - 1]);
            }
        }
    } else {
        std::cout << "here" << std::endl;
        L.insert(std::lower_bound(L.begin(), L.end(), S[0]), S[0]);
    }

    // Step 5: Insert the "struggle" element if it exists
    if (struggle != -1)
    {
        typename T::iterator pos = std::lower_bound(L.begin(), L.end(), struggle);
        L.insert(pos, struggle);
    }

    // Step 6: copy sorted elements back to the original sequence
    seq = L;
}