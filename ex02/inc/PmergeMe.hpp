#pragma once

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>

#include <deque>
#include <vector>

class PmergeMe
{
    public:
        PmergeMe();
        PmergeMe(PmergeMe &src);
        PmergeMe&operator=(PmergeMe &src);
        ~PmergeMe();

        void insert(unsigned int value);

        void fordJohnsonSort(void);

        void dequeSpitter(void);
        void vectorSpitter(void);

        void displayTime(void);

    private:
        std::deque<unsigned int>    dque;
        std::vector<unsigned int>   vect;

        float dqueTime;
        float vectTime;
};