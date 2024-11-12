#include "PmergeMe.hpp"
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <deque>
#include <iostream>
#include <ctime>

PmergeMe::PmergeMe(const std::vector<int>& seq) : sequence(seq) {}

void PmergeMe::sortWithVector() {
    clock_t start = clock();
    std::vector<int> seqCopy = sequence;
    mergeInsertSort(seqCopy);
    clock_t end = clock();
    displaySequence(seqCopy, "After:");
    displayTime(static_cast<double>(end - start) / CLOCKS_PER_SEC * 1e6, "std::vector");
}

void PmergeMe::sortWithDeque() {
    clock_t start = clock();
    std::deque<int> seqCopy(sequence.begin(), sequence.end());
    mergeInsertSort(seqCopy);
    clock_t end = clock();
    displayTime(static_cast<double>(end - start) / CLOCKS_PER_SEC * 1e6, "std::deque");
}

void PmergeMe::displaySequence(const std::vector<int>& seq, const std::string& msg) {
    std::cout << msg << " ";
    for (size_t i = 0; i < seq.size(); ++i) {
        std::cout << seq[i] << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::displaySequence(const std::deque<int>& seq, const std::string& msg) {
    std::cout << msg << " ";
    for (size_t i = 0; i < seq.size(); ++i) {
        std::cout << seq[i] << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::displayTime(double time, const std::string& containerType) {
    std::cout << "Time to process with " << containerType << ": " << time << " us" << std::endl;
}

std::vector<int> PmergeMe::jacobsthalSequence(int n) {
    std::vector<int> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    while (jacobsthal.size() < static_cast<std::size_t>(n)) {
        int next = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
        jacobsthal.push_back(next);
    }
    return jacobsthal;
}

template <typename T>
void PmergeMe::mergeInsertSort(T& seq) {
    if (seq.size() < 2) return; // Base case for trivial sorting

    // Step 1: Pair elements and sort each pair
    std::vector<std::pair<int, int> > pairs;  // Add a space between consecutive right angle brackets
    for (size_t i = 0; i < seq.size() - 1; i += 2) {
        if (seq[i] > seq[i + 1]) {
            pairs.push_back(std::make_pair(seq[i], seq[i + 1]));
        } else {
            pairs.push_back(std::make_pair(seq[i + 1], seq[i]));
        }
    }
    // Handle odd element if it exists (the "struggle" element)
    int struggle = (seq.size() % 2 != 0) ? seq.back() : -1;

    // Step 2: Sort pairs by the larger element (first in pair)
    std::sort(pairs.begin(), pairs.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.first < b.first;
    });

    // Step 3: Separate into B and S sequences
    T B; // Sorted larger elements
    T S; // Unsorted smaller elements
    for (size_t i = 0; i < pairs.size(); ++i) {
        B.push_back(pairs[i].first);
        S.push_back(pairs[i].second);
    }

    // Step 4: Insert elements from S into B using Ford-Johnson (Jacobsthal order)
    std::vector<int> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    for (size_t i = 2; i < S.size(); ++i) {
        jacobsthal.push_back(jacobsthal[i - 1] + 2 * jacobsthal[i - 2]);
    }

    for (size_t j = 0; j < S.size(); ++j) {
        size_t insertIndex = jacobsthal[j];
        if (insertIndex >= B.size()) insertIndex = B.size() - 1;

        // Find position using binary search in the limited range
        typename T::iterator pos = std::lower_bound(B.begin(), B.begin() + insertIndex + 1, S[j]);
        B.insert(pos, S[j]);
    }

    // Step 5: Insert the "struggle" element if it exists
    if (struggle != -1) {
        typename T::iterator pos = std::lower_bound(B.begin(), B.end(), struggle);
        B.insert(pos, struggle);
    }

    // Step 6: Copy sorted elements back to the original sequence
    seq = B;
}
