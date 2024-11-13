#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <string>

class PmergeMe
{
private:
    std::vector<int> sequence;
    static std::vector<int> jacobsthalSequence(int n);
    template <typename T>
    void mergeInsertSort(T& seq);

public:
    PmergeMe(const std::vector<int>& sequence);
    void sortWithVector();
    void sortWithDeque();
    void displaySequence(const std::vector<int>& sequence, const std::string& msg);
    void displaySequence(const std::deque<int>& sequence, const std::string& msg);
    void displayTime(double time, const std::string& containerType);

    int Jacobsthal(int n);
    std::vector<unsigned long> jacobIndexGeneratorVector(std::vector<int> &jacobsthals, int size);
    int returnIndexVector(std::vector<int> &v, int value);
};

#endif