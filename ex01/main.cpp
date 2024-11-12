#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Usage: " << av[0] << " \"expression\"" << std::endl;
        return (1);
    }

    RPN rpnCalculator;
    rpnCalculator.evaluate(av[1]);
    
    return (0);
}
