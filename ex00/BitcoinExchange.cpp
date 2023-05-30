/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:40:45 by cudoh             #+#    #+#             */
/*   Updated: 2023/05/21 16:40:45 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(char const *fp) : dbFlag(true)
{
    std::string fpStr(fp);
    std::ifstream dbInpFileStream;
    std::string dateStr;
    std::string rateStr;
    float rateFloat = 0.0;


    try
    {
        if (!isFileFormatValid(fpStr)) // check that file format is valid
            throw std::runtime_error(ERR_MSG_InvalidFileFmt);

        // open file -
        if (!isFileOpen(fp, dbInpFileStream))
            throw std::runtime_error(ERR_MSG_FileOpenFailed);

        // is file empty
        if (!isFileEmpty(dbInpFileStream))
        {

            std::getline(dbInpFileStream, dateStr);
            for (int x = 0; x < 10; x++)
            {
                if (dbInpFileStream.good())
                {
                    std::getline(dbInpFileStream, dateStr, DELIMITER_COMMA);
                    if (!isDateValid(dateStr))
                    {
                        std::cerr << COL_RED "Error! bad input => " COL_DEFAULT
                        << dateStr << ENDL; 
                    }

                    std::getline(dbInpFileStream, rateStr);
                    if (isFloatValid(rateStr))
                    {
                        rateFloat = std::strtof(rateStr.c_str(), NULL);
                        db.insert(pairType(dateStr, rateFloat));
                        COUT << dateStr << ENDL;
                    }
                }
                else
                    break;
            }
        }
        // create the db map
        dbInpFileStream.close();
    }
    EXCEPTION_HANDLER();
}

bool BitcoinExchange::isDateValid(std::string &Str)
{
    bool result = false;
    std::stringstream dateStream(Str);
    int y=0, m=0, d=0;
    struct tm t;
    struct tm *nt;
    time_t  when;
    char delimiter;

    memset((void *)&t, 0, sizeof(tm));
    stripWhiteSpace(Str);
    try
    {
        dateStream >> y >> delimiter >> m >> delimiter >> d;
        t.tm_year = y - 1900;
        t.tm_mon = m - 1;
        t.tm_mday = d;
        t.tm_isdst = -1;
        if (t.tm_year <= 0 || t.tm_mon <= 0 || t.tm_mday <= 0)
        {
            return (result);

        }

        when = mktime(&t);
        nt = localtime(&when);
        result = (nt->tm_year == t.tm_year &&
                  nt->tm_mon == t.tm_mon &&
                  nt->tm_mday == t.tm_mday);
#ifdef _DEBUG_
        COUT << y << ENDL;
        COUT << m << ENDL;
        COUT << d << ENDL;
#endif
    }
    EXCEPTION_HANDLER();

    return (result);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &obj)
{
    db = obj.db;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &obj)
{
    db = obj.db;
    return (*this);
}

BitcoinExchange::~BitcoinExchange(void) {}

dbType &BitcoinExchange::getDb(void)
{
    return (db);
}

bool BitcoinExchange::isFileFormatValid(std::string const &fpStr)
{
    bool result = false;
    std::size_t idx = 0;
    std::string fmtStr(FILE_FMT);

    idx = fpStr.rfind(fmtStr);
    if (idx != std::string::npos)
    {
#ifdef _DEBUG_
        COUT << "FOUND : " << idx << " -> " << fpStr.substr(idx + 1) << ENDL;
#endif // DEBUG
        if (fpStr.substr(idx) == fmtStr)
        {
#ifdef _DEBUG_
            COUT << "end of file name" << ENDL;
#endif // DEBUG
            result = true;
        }
    }
    return (result);
}

bool BitcoinExchange::isFileOpen(char const *fp, std::ifstream &ifs)
{
    bool result = false;

    ifs.open(fp, std::ifstream::in);
    if (ifs.good())
        result = true;
    return (result);
}

bool BitcoinExchange::isFileEmpty(std::ifstream &ifs)
{
    bool result = false;
    int length;
    ifs.seekg(0, ifs.end);
    length = ifs.tellg();
    ifs.seekg(0, ifs.beg);
#ifdef _DEBUG_
    COUT << "file size: " << length << " bytes." << ENDL;
#endif // DEBUG
    if (length == 0)
        result = true;
    return (result);
}

void BitcoinExchange::stripWhiteSpace(std::string &str)
{
    std::string::size_type found = str.find_first_not_of(CHARS_WHITESPACE);

    // remove all leading whitespace characters
    if (found != std::string::npos)
    {
        str = str.substr(found);
    }
    else
    {
        str.clear();
    }

    // remove all trailing whitespace characters
    if (str.size() > 0)
    {
        found = str.find_last_not_of(CHARS_WHITESPACE);
        if (found != std::string::npos)
        {
            str.erase(found + 1);
        }
        else
        {
            str.clear();
        }
    }
#ifdef _DEBUG_
    COUT << str << ENDL;
#endif
}

bool BitcoinExchange::isSpaceInStr(std::string &str)
{
    std::string::size_type found = str.find_first_of(CHARS_WHITESPACE);
    bool result = false;

    if (found != std::string::npos)
    {
        result = true;
    }
    return (result);
}

bool BitcoinExchange::isFloatValid(std::string &valueStr)
{
    bool result = false;
    std::stringstream sStream(valueStr);
    float valueFloat = 0.0;
    
    stripWhiteSpace(valueStr);
    try
    {
        if (isSpaceInStr(valueStr))
        {
            throw std::runtime_error(ERR_MSG_InvalidFmtSpace);
        }
        else if (valueStr.find_first_not_of(CHARS_VALID_FLOAT) != std::string::npos)
        {
            throw std::runtime_error(ERR_MSG_InvalidFmtBadChar);
        }
        if (sStream >> valueFloat)
        {
            COUT << valueStr << " -> " << valueFloat << ENDL;
            if (valueFloat < 0 || valueFloat > MAX_VALUE)
            {
                throw std::runtime_error(ERR_MSG_InvalidValueRange);
            }

            result = true;
        }
        else
        {
            throw std::runtime_error(ERR_MSG_InvalidFloat);
        }
    }
    EXCEPTION_HANDLER();
    return (result);
}

std::ostream &operator<<(std::ostream &o, BitcoinExchange &btc)
{
    dbType db = btc.getDb();
    dbType::iterator it;

    if (db.size() > 0)
    {
        it = db.begin();
#ifdef _DEBUG_
        COUT << "exchange is ongoing" << ENDL;
#endif // DEBUG
        while (it != db.end())
        {
            COUT << (*it).first << " | " << (*it).second << ENDL;
            it++;
        }
    }
    return (o);
}
