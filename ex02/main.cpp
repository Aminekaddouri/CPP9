#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <sstream>

int stringToInt(const std::string& str) {
    std::stringstream ss(str);
    int num;
    ss >> num;
    if (ss.fail()) {
        throw std::invalid_argument("Invalid integer string: " + str);
    }
    return num;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error: No sequence provided." << std::endl;
        return 1;
    }

    try {
        std::vector<int> sequence;
        for (int i = 1; i < argc; ++i) {
            int num = stringToInt(argv[i]);
            if (num <= 0) throw std::invalid_argument("Error: Only positive integers are allowed.");
            sequence.push_back(num);
        }

        PmergeMe pmerge(sequence);

        // Display "Before" sequence
        std::cout << "Before:";
        for (const int& num : sequence) std::cout << " " << num;
        std::cout << std::endl;

        // Perform sorting and timing
        pmerge.sortWithVector();
        pmerge.sortWithDeque();

    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
