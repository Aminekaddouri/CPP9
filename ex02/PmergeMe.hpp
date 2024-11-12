#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <string>

class PmergeMe {
public:
    PmergeMe(const std::vector<int>& sequence);
    void sortWithVector();
    void sortWithDeque();
    void displaySequence(const std::vector<int>& sequence, const std::string& msg);
    void displaySequence(const std::deque<int>& sequence, const std::string& msg);
    void displayTime(double time, const std::string& containerType);

private:
    std::vector<int> sequence;
    std::vector<int> jacobsthalSequence(int n);
    template <typename T>
    void mergeInsertSort(T& seq);
    // void mergeInsertSort(std::vector<int>& seq);
    // void mergeInsertSort(std::deque<int>& seq);
};

#endif
