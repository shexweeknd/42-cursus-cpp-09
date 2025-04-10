#include "PmergeMe.hpp"

// canonical form
PmergeMe::PmergeMe(void): dqueTime(0), vectTime(0)
{}

PmergeMe::PmergeMe(PmergeMe &src): dqueTime(0), vectTime(0)
{
    *this = src;
}

PmergeMe& PmergeMe::operator=(PmergeMe &src)
{
    if (this == &src)
        return (*this);

    this->dqueTime = src.dqueTime;
    this->vectTime = src.vectTime;

    this->dque.clear();
    this->vect.clear();

    for (std::deque<unsigned int>::const_iterator it = src.dque.begin(); it != src.dque.end(); it++)
    {
        this->dque.push_back(*it);
        this->vect.push_back(*it);
    }
    return (*this);
}

PmergeMe::~PmergeMe(void)
{}

// methods
void PmergeMe::insert(unsigned int value)
{
    this->dque.push_back(value);
    this->vect.push_back(value);
}

// a implementer
void PmergeMe::fordJohnsonSort(void)
{
    // time pour deque
    // sort deque
    // time pour vect
    // sort vect
}

void PmergeMe::dequeSpitter(void)
{
    for (std::deque<unsigned int>::const_iterator it = this->dque.begin(); it != this->dque.end(); it++)
        std::cout << *it << (it + 1 != this->dque.end() ? " " : "");
}

void PmergeMe::vectorSpitter(void)
{
    for (std::vector<unsigned int>::const_iterator it = this->vect.begin(); it != this->vect.end(); it++)
        std::cout << *it << (it + 1 != this->vect.end() ? " " : "");
}

void PmergeMe::displayTime(void)
{
    std::cout << "Time to process a range of " << dque.size() << " elements with std::deque<unsigned int> : " << this->dqueTime << " us" << std::endl;

    std::cout << "Time to process a range of " << vect.size() << " elements with std::vect<unsigned int> : " << this->vectTime << " us" << std::endl;
}