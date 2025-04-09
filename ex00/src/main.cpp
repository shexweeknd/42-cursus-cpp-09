#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    std::string db = "./assets/data.csv";
    if (argc != 2)
    {
        std::cerr << "\e[31mError: wrong number of args\e[0m" << std::endl;
        return (1);
    }
    BitcoinExchange btc;

    try
    {
        // store _db data in a map
        // std::cout << std::endl << "========loading db============" << std::endl;
        btc.dbInsert(db);
        // std::cout << std::endl << "==============================" << std::endl;
        
        // compute output
        // std::cout << std::endl << "========computing input=======" << std::endl;
        btc.computeInput(argv[1]);
        // std::cout << std::endl << "==============================" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return (0);
}
