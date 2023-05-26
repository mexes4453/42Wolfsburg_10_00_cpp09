/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:40:42 by cudoh             #+#    #+#             */
/*   Updated: 2023/05/21 16:40:42 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <map>
# include <iostream>
# include <stdexcept>
# include <fstream>
# include <cstdlib>
# include <sstream>
# include <utility>
# include <algorithm>

# define COUT std::cout
# define ENDL std::endl
# define COL_BLUE "\033[0;34m"
# define COL_RED "\033[0;31m"
# define COL_YELLOW "\033[0;33m"
# define COL_MAGENTA "\033[0;35m"
# define COL_DEFAULT "\033[0m"

# define FILE_FMT (".csv")
# define ERR_MSG_NoInputFile    ("Error: No input file.")
# define ERR_MSG_ToManyArgs     ("Error: Too many args.")
# define ERR_MSG_InvalidFileFmt ("Error: Invalid file format.")
# define ERR_MSG_FileOpenFailed ("Error: could not open file")
# define SHOW_HEADER(MSG) COUT << ENDL << COL_YELLOW "== "#MSG" ==" COL_DEFAULT << ENDL; 
# define EXCEPTION_HANDLER()            \
    catch (const std::exception &e)     \
    {\
        std::cerr << e.what() << '\n'; \
    }\

typedef std::map<std::string, float>    dbType;
typedef std::pair<std::string, float>   pairType;
class BitcoinExchange
{
    private:
        dbType  db;
        //bool    file_state;
        bool    isFileFormatValid(std::string const &fpStr);
        bool    isFileOpen(char const *fp, std::ifstream &ifs);
        bool    isFileEmpty(std::ifstream &ifs);
        BitcoinExchange(void);

    public:
        BitcoinExchange(char const *fp);
        BitcoinExchange(BitcoinExchange const &obj);
        BitcoinExchange &operator=(BitcoinExchange const &obj);
        ~BitcoinExchange(void);
        dbType &getDb(void);

};

std::ostream    &operator<<(std::ostream &o, BitcoinExchange &btc);

#endif  //BITCOINEXCHANGE_HPP
