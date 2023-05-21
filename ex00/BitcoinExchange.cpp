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

BitcoinExchange::BitcoinExchange(void){}

BitcoinExchange::BitcoinExchange(char const *fp)
{
    std::string     fpStr(fp);
    std::ifstream   dbInpFileStream;
    char            bufStr[500];

    try
    {
        if (!isFileFormatValid(fpStr)) // check that file format is valid
            throw   std::runtime_error(ERR_MSG_InvalidFileFmt);
        
        // open file - 
        if (!isFileOpen(fp, dbInpFileStream))
            throw std::runtime_error(ERR_MSG_FileOpenFailed);

        // is file empty
        if (!isFileEmpty(dbInpFileStream))
        {
            for (int x = 0; x < 10; x++)
            {
                if (dbInpFileStream.good())
                {
                    dbInpFileStream.getline(bufStr, 1000);
                    COUT << bufStr << ENDL;
                }
            }
        }
        // create the db map
        dbInpFileStream.close();
    }
    EXCEPTION_HANDLER();
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


BitcoinExchange::~BitcoinExchange(void){}


dbType &BitcoinExchange::getDb(void)
{
    return (db);
}


bool    BitcoinExchange::isFileFormatValid(std::string const &fpStr)
{
    bool            result = false;
    std::size_t     idx = 0;
    std::string     fmtStr(FILE_FMT);

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


bool    BitcoinExchange::isFileOpen(char const *fp, std::ifstream &ifs)
{
    bool    result = false;
    
    ifs.open(fp, std::ifstream::in);
    if (ifs.good())
        result = true;
    return (result);
}


bool    BitcoinExchange::isFileEmpty(std::ifstream &ifs)
{
    bool    result = false;
    int     length;
    ifs.seekg (0, ifs.end);
    length = ifs.tellg();
    ifs.seekg (0, ifs.beg);
#ifdef _DEBUG_
    COUT << "file size: " << length << " bytes." << ENDL;
#endif // DEBUG
    if (length == 0)
        result = true;
    return (result);
}

std::ostream    &operator<<(std::ostream &o, BitcoinExchange &btc)
{
    dbType db = btc.getDb();

    if (db.size() > 0)
    {
        COUT << "exchange is ongoing" << ENDL;
    }
    return (o);
}

