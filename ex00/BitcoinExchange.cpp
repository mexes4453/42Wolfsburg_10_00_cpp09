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
    readDbFile();
    readInputFile(fp);
}

bool BitcoinExchange::isDateValid(std::string &Str)
{
    bool                result = false;
    std::stringstream   dateStream(Str);
    struct tm           t;
    struct tm           *nt;
    time_t              when;
    char                delimiter;
    int y=0, m=0, d=0, ny=0, nm=0, nd=0;

    memset((void *)&t, 0, sizeof(tm));
    stripWhiteSpace(Str);
    try
    {
        dateStream >> y >> delimiter >> m >> delimiter >> d;
        t.tm_year = y - 1900;
        t.tm_mon = m - 1;
        t.tm_mday = d;
        t.tm_isdst = -1;
        if (t.tm_year < 0 || t.tm_mon < 0 || t.tm_mday < 0)
        {
            //throw std::runtime_error(ERR_MSG_NegativeDateComp);
            goto end;
        }
        when = mktime(&t);
        nt = localtime(&when);
        dateStream.clear();
        dateStream.str(asctime(nt));
        
        validateDateValue(dateStream, nm, ny, nd);

        //use time diff to check if data is in future
#ifdef _DEBUG_
        COUT << "Time difference: " << difftime(time(NULL), when) << ENDL;
#endif
        if (difftime(time(NULL), when) < 0)
        {
            //throw std::runtime_error(ERR_MSG_DateInFuture);
            goto end;
        }
        result = (y == ny && m == nm && d == nd);
#ifdef _DEBUG_
        //COUT << dateTimeStr << ENDL;
        COUT << y << " : " << ny << ENDL;
        COUT << m << " : " << nm << ENDL;
        COUT << d << " : " << nd << ENDL;
#endif
    }
    EXCEPTION_HANDLER();
end:
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
#ifdef _DEBUG_            
            COUT << valueStr << " -> " << valueFloat << ENDL;
#endif
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

int    BitcoinExchange::convertMonthStrToInt(std::string &str)
{
    int result = -1;
    static std::string months[12] = {
                                     "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                     "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
                                    };
    int x = 0;
    while (x < 12)
    {
        if (months[x] == str)
        {
            result = x + 1;
            break ;
        }
        x++;
    }
    return (result);
}

void BitcoinExchange::validateDateValue(std::stringstream &ss,
                                        int &nm, int &ny, int &nd)
{
    std::string tok;
    int x = 0, z = 0;
    while (std::getline(ss, tok, ' '))
    {
        if (tok.size() > 0)
        {
            z++;
#ifdef _DEBUG_
            COUT << x << " - " << tok << ENDL;
#endif
            switch (z)
            {
            case 2:
            {
                nm = convertMonthStrToInt(tok);
                break;
            }
            case 3:
            {
                nd = (strtof(tok.c_str(), NULL));
                break;
            }
            case 5:
            {
                ny = (strtof(tok.c_str(), NULL));
                break;
            }
            default:
            {
            }
            }
        }
        x++;
    }
}
void    BitcoinExchange::readDbFile(void)
{
    std::string fpStr(FILE_DB);
    std::ifstream dbInpFileStream;
    std::string lineStr = "";
    std::string dateStr;
    std::string rateStr;
    std::string::size_type found = 0;
    float rateFloat = 0.0;


    try
    {
        if (!isFileFormatValid(fpStr)) // check that file format is valid
            throw std::runtime_error(ERR_MSG_InvalidFileFmt);

        // open file -
        if (!isFileOpen(FILE_DB, dbInpFileStream))
            throw std::runtime_error(ERR_MSG_FileOpenFailed);

        // is file empty
        if (!isFileEmpty(dbInpFileStream))
        {

            // std::getline(dbInpFileStream, dateStr);
            std::getline(dbInpFileStream, lineStr);
            for (int x = 0; x < 20; x++)
            {
                if (dbInpFileStream.good())
                {
                    std::getline(dbInpFileStream, lineStr);
#ifdef _DEBUG_
                    COUT << "-------------------------------------------" << ENDL;
#endif
                    found = lineStr.find(DELIMITER_COMMA);
                    if (found != std::string::npos)
                    {
                        dateStr = lineStr.substr(0, found);
                        rateStr = lineStr.substr(found + 1);
#ifdef _DEBUG_
                        COUT << "date string : " << dateStr << ENDL;
                        COUT << "rate string : " << rateStr << ENDL;
#endif
                        if (!isDateValid(dateStr))
                        {
                            std::cerr << COL_RED "Error! bad input => " 
                                      << dateStr << COL_DEFAULT << ENDL;
                            continue;
                        }
                        if (isFloatValid(rateStr))
                        {
                            rateFloat = std::strtof(rateStr.c_str(), NULL);
                            db.insert(pairType(dateStr, rateFloat));
#ifdef _DEBUG_
                            COUT << rateStr << ENDL;
#endif
                        }
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


void    BitcoinExchange::readInputFile(char const *fp)
{
    std::string fpStr(fp);
    std::ifstream dbInpFileStream;
    std::string lineStr = "";
    std::string dateStr;
    std::string rateStr;
    std::string::size_type found = 0;
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

            // std::getline(dbInpFileStream, dateStr);
            std::getline(dbInpFileStream, lineStr);
            for (int x = 0; x < 20; x++)
            {
                if (dbInpFileStream.good())
                {
                    std::getline(dbInpFileStream, lineStr);
#ifdef _DEBUG_
                    COUT << "-------------------------------------------" << ENDL;
                    COUT << "--> " << lineStr << ENDL;
#endif
                    found = lineStr.find(DELIMITER_PIPE);
                    if (found != std::string::npos)
                    {
                        dateStr = lineStr.substr(0, found);
                        rateStr = lineStr.substr(found + 1);
#ifdef _DEBUG_
                        COUT << "date string : " << dateStr << ENDL;
                        COUT << "rate string : " << rateStr << ENDL;
#endif
                        if (!isDateValid(dateStr))
                        {
                            std::cerr << COL_RED "Error! bad input => " 
                                      << dateStr << COL_DEFAULT << ENDL;
                            continue;
                        }
                        if (isFloatValid(rateStr))
                        {
                            rateFloat = std::strtof(rateStr.c_str(), NULL);
                            //db.insert(pairType(dateStr, rateFloat));
                            // search database and perform exchange operation
                            COUT << "input file : " << dateStr << " = " << rateStr
                                << rateFloat << ENDL;
#ifdef _DEBUG_
                            COUT << rateStr << ENDL;
#endif
                        }
                    }
                    else
                    {
                        std::cerr << COL_RED "Error! bad input => " 
                                      << lineStr << COL_DEFAULT << ENDL;
                        continue;
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
