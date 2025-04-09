#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{}

BitcoinExchange::BitcoinExchange(BitcoinExchange &src): std::map<std::string, float>(src)
{
    *this = src;
}

BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange &src)
{
    if (this == &src)
        return (*this);
    this->clear();
    std::map<std::string, float>::operator=(src);
    for (BitcoinExchange::const_iterator it = src.begin(); it != src.end(); it++)
        this->insert(std::pair<std::string, float>(it->first, it->second));
    return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{}

// utils methods
void BitcoinExchange::printData(void) const
{
    for (BitcoinExchange::const_iterator it = this->begin(); it != this->end(); it++)
        std::cout << "\e[33mkey: " << it->first << " value: " << it->second << std::endl;
}

bool BitcoinExchange::isLeapYear(int year) const
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Database processing
// YYYY-MM-DD
bool BitcoinExchange::isValidDateFormat(std::string date, const std::string line) const
{
    (void)line;
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return (false);
    for (size_t i = 0; i < date.length() ; i++)
    {
        if (date[i] == '-' || date[i] == '-')
            continue;
        if (!std::isdigit(date[i]))
            return (false);
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 7).c_str());
    int day = std::atoi(date.substr(8, 10).c_str());

    if (year < 2009)
        return (false);
    else if (month < 1 || month > 12)
        return (false);

    int daysInMonth[12] = { 31, 28, 31, 30, 31, 30,
                            31, 31, 30, 31, 30, 31 };

    if (month == 2 && this->isLeapYear(year))
        daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1])
        return (false);

    return (true);
}

// middleware of db file
bool BitcoinExchange::isValidRateFormat(std::string rate, const std::string line) const
{
    (void)line;
    float   _ratef;
    size_t  _dotocc;

    _dotocc = 0;
    for (size_t i = 0; i < rate.length(); i++)
        if (rate[i] == '.') _dotocc++;
    if (_dotocc > 1 || rate[rate.length() - 1] == '.')
        return (false);
    for (size_t i = 0; i < rate.length(); i++)
    {
        if (!std::isdigit(rate[i]) && rate[i] != '.')
            return (false);
    }
    if (std::atof(rate.c_str()) < 0)
        return (false);
    if (std::atof(rate.c_str()) >= static_cast<float>(2147483648))
        return (false);
    return (true);
}

// middleware of input file
bool BitcoinExchange::isValidValueFormat(std::string cmp, const std::string line) const
{
    float   _ratef;
    size_t  _dotocc;

    if (cmp.empty() || cmp.length() < 4)
        return (false);

    _dotocc = 0;
    for (size_t i = 0; i < cmp.length(); i++)
        if (cmp[i] == '.') _dotocc++;

    if (_dotocc > 1 || cmp[cmp.length() - 1] == '.' || (cmp.substr(0, cmp.find_last_of(" ") + 1).compare(" | ")))
    {
        std::cout << "\e[31mError: bad input => " + line + "\e[0m" << std::endl;
        return (false);
    }

    cmp = cmp.substr(3, cmp.length());
    for (size_t i = 0; i < cmp.length(); i++)
    {
        if (std::atof(cmp.c_str()) < 0)
        {
            std::cout << "\e[31mError: not a positive number.\e[0m" << std::endl;
            return (false);
        }
        else if (!std::isdigit(cmp[i]) && cmp[i] != '.')
        {
            std::cout << "\e[31mError: bad input => " + line + "\e[0m" << std::endl;
            return (false);
        }
    }
    _ratef = std::atof(cmp.c_str());
    if (_ratef >= static_cast<float>(2147483648))
    {
        std::cout << "\e[31mError: too large a number." << "\e[0m" << std::endl;
        return (false);
    }
    return (true);
}

// db loader in memory
void BitcoinExchange::dbInsert(std::string db)
{
    std::string     line;
    std::fstream    file(db.c_str());

    if (!file.is_open())
        throw std::runtime_error("\e[31mError: unable to open " + db + "\e[0m");
    
    std::getline(file, line);
    
    if (line.empty())
        throw std::runtime_error("\e[31m" + db + ": empty Database\e[0m");

    if (line.compare("date,exchange_rate") != 0)
        throw std::runtime_error("\e[31mError: misconfigured db ⇒ " + line + "\e[0m");
    
    while (std::getline(file, line))
    {
        if (line.length() <= 11 || !isValidDateFormat(line.substr(0, line.find(",")), line) || !isValidRateFormat(line.substr(11, line.find(EOF)), line))
        {
            std::cout << "\e[31mError: " << db << " non valid entry -> " << line << "\e[0m" << std::endl;
            continue;
        }
        this->insert(std::pair<std::string, float>(line.substr(0, line.find(",")), std::atof(line.substr(11, line.find(EOF)).c_str())));
        // std::cout << "\e[32m" << db << ": loaded record -> " << line << "\e[0m" << std::endl;
    }
}

// Output result
void BitcoinExchange::outputResult(std::string key, float value) const
{
    float result;

    BitcoinExchange::const_iterator it = this->lower_bound(key);

    if (it != this->end() && !it->first.compare(key))
        result = it->second * value;
    else if (it == this->begin())
    {
        std::cout << "\e[31mError: not found because no nearest date.\e[0m" << std::endl;
        return;
    }
    else
        result = (--it)->second * value;
    std::cout << "\e[32m" << key << " => " << value << " = " << result << std::endl;
}

// Input parser
void BitcoinExchange::computeInput(std::string input)
{
    std::string     line;
    std::fstream    file(input.c_str());

    if (!file.is_open())
        throw std::runtime_error("\e[31mError: unable to open " + input + "\e[0m");

    std::getline(file, line);
    if (line.empty())
        throw std::runtime_error("\e[31m" + input + ": empty evaluation file\e[0m");

    if (line.compare("date | value") != 0)
        throw std::runtime_error("\e[31mError: misconfigured evaluation file ⇒ " + line + "\e[0m");

    while (std::getline(file, line))
    {
        if (!isValidDateFormat(line.substr(0, line.find(" ")), line) || line.length() < 14)
        {
            std::cout << "\e[31mError: bad input => " + line + "\e[0m" << std::endl;
            continue;
        }
        else if (!isValidValueFormat(line.substr(10, line.find(EOF)), line))
            continue;
        this->outputResult(line.substr(0, line.find(" ")), atof(line.substr(13, line.find(EOF)).c_str()));
    }
}
