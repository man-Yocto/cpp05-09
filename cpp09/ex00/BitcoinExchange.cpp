#include "BitcoinExchange.hpp"


namespace
{
    std::string trim(const std::string& text)
    {
        std::string::size_type first = 0;
        std::string::size_type last = text.length();

        while (first < last && std::isspace(static_cast<unsigned char>(text[first])))
            ++first;
        while (last > first && std::isspace(static_cast<unsigned char>(text[last - 1])))
            --last;
        return text.substr(first, last - first);
    }

    int toInt(const std::string& value)
    {
        std::istringstream stream(value);
        int result;
        stream >> result;
        return result;
    }

    bool isLeapYear(int year)
    {
        return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    }
}

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _db(other._db)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
        _db = other._db;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDatabase(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    std::string line;

    if (!file)
        throw std::runtime_error("Error: could not open database.");
    _db.clear();
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::string::size_type comma = line.find(',');
        if (comma == std::string::npos)
            continue;

        std::string date = trim(line.substr(0, comma));
        std::string priceText = trim(line.substr(comma + 1));
        char* end = 0;
        errno = 0;
        double price = std::strtod(priceText.c_str(), &end);
        if (!date.empty() && end != priceText.c_str() && *end == '\0'
            && errno != ERANGE)
            _db[date] = static_cast<float>(price);
    }
    if (_db.empty())
        throw std::runtime_error("Error: database is empty.");
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    for (std::string::size_type i = 0; i < date.length(); ++i)
    {
        if (i != 4 && i != 7 && !std::isdigit(static_cast<unsigned char>(date[i])))
            return false;
    }

    int year = toInt(date.substr(0, 4));
    int month = toInt(date.substr(5, 2));
    int day = toInt(date.substr(8, 2));
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month < 1 || month > 12)
        return false;
    if (month == 2 && isLeapYear(year))
        daysInMonth[1] = 29;
    return day >= 1 && day <= daysInMonth[month - 1];
}

bool BitcoinExchange::isValidValue(const std::string& value, float& outValue) const
{
    char* end = 0;
    errno = 0;
    double parsed = std::strtod(value.c_str(), &end);

    if (value.empty() || end == value.c_str() || *end != '\0' || errno == ERANGE
        || parsed != parsed)
        return false;
    if (parsed < 0.0 || parsed > 1000.0)
        return false;
    outValue = static_cast<float>(parsed);
    return true;
}

float BitcoinExchange::getRate(const std::string& date) const
{
    std::map<std::string, float>::const_iterator it = _db.lower_bound(date);

    if (it != _db.end() && it->first == date)
        return it->second;
    if (it == _db.begin())
        throw std::out_of_range("Error: no exchange rate available for this date.");
    if (it == _db.end() || it->first != date)
        --it;
    return it->second;
}

void BitcoinExchange::processInputFile(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    std::string line;

    if (!file)
        throw std::runtime_error("Error: could not open file.");
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::string::size_type separator = line.find('|');
        if (separator == std::string::npos || line.find('|', separator + 1) != std::string::npos)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0, separator));
        std::string valueText = trim(line.substr(separator + 1));
        float value;
        if (!isValidDate(date))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (!isValidValue(valueText, value))
        {
            char* end = 0;
            double raw = std::strtod(valueText.c_str(), &end);
            if (end != valueText.c_str() && *end == '\0' && raw < 0.0)
                std::cout << "Error: not a positive number." << std::endl;
            else if (end != valueText.c_str() && *end == '\0' && raw > 1000.0)
                std::cout << "Error: too large a number." << std::endl;
            else
                std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        try
        {
            std::cout << date << " => " << value << " = " << getRate(date) * value << std::endl;
        }
        catch (const std::exception& error)
        {
            std::cout << error.what() << std::endl;
        }
    }
}
