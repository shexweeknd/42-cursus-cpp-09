#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <exception>
#include <map>

// mettre toutes les fonctions en methode de la classe BitcoinExchange

class BitcoinExchange: public std::map<std::string, float>
{
    public:
        BitcoinExchange(void);
        BitcoinExchange(BitcoinExchange &src);
        BitcoinExchange&operator=(BitcoinExchange &src);
        ~BitcoinExchange(void);

        void dbInsert(std::string db);
        void computeInput(std::string input);

    private:
        bool isLeapYear(int year) const;
        bool isValidDateFormat(std::string date, const std::string line) const;
        bool isValidRateFormat(std::string rate, const std::string line) const;
        bool isValidValueFormat(std::string cmp, const std::string line) const;

        void outputResult(std::string key, float value) const;

        void printData(void) const;
};