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

        void insertDeque(unsigned int value);
        void insertVector(unsigned int value);

        void sortDeque(void);
        void sortVector(void);

        void dequeSpitter(void);
        void vectorSpitter(void);

        void displayDequeTime(void);
        void displayVectorTime(void);

    private:
        std::deque<unsigned int> dque;
        std::vector<unsigned int> vect;

        float dqueTime;
        float vectTime;
};