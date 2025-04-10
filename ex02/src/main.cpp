#include "PmergeMe.hpp"

int valid_args(std::string arg)
{
    for (size_t i = 0; i < arg.length(); i++)
        if (!isdigit(arg[i]))
            return (0);
    return (1);
}

int main(int argc, char **argv)
{
    PmergeMe merger;

    if (argc < 2 || !valid_args(argv[1]))
    {
        std::cout << "\e[31mError: argument invalid\e[0m" << std::endl;
        return (1);
    }
    for (size_t i = 0; argv[i]; i++)
        merger.insert(atoi(argv[i]));
    std::cout << "Before:   "; merger.dequeSpitter(); std::cout << std::endl;

    merger.fordJohnsonSort();

    std::cout << "After:    "; merger.dequeSpitter(); std::cout << std::endl;

    merger.displayTime();

    return (0);
}
