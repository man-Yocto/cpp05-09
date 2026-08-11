#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <cctype>
#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

class BitcoinExchange
{
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void loadDatabase(const std::string& filename);
        void processInputFile(const std::string& filename);

    private:
        std::map<std::string, float> _db;

        bool isValidDate(const std::string& date) const;
        bool isValidValue(const std::string& value, float& outValue) const;
        float getRate(const std::string& date) const;
};

#endif
