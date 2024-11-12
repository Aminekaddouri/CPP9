#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange
{
private:
    std::map<std::string, double> exchangeRates;

public:
    BitcoinExchange();
    BitcoinExchange(const std::string& databaseFile);
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    double getExchangeRate(const std::string &data) const;
    void processInputFile(const std::string &inputFile) const;
};

#endif