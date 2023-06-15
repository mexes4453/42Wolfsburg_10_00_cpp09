/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPH.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 20:49:17 by cudoh             #+#    #+#             */
/*   Updated: 2023/06/11 20:49:17 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPH_HPP
# define RPH_HPP
# include <iostream>
# include <stdexcept>
# include <fstream>
# include <sstream>
# include <string>
# include <cstring>
# include <utility>
# include <algorithm>
# include <stack>

# define COUT std::cout
# define ENDL std::endl
# define COL_BLUE "\033[0;34m"
# define COL_RED "\033[0;31m"
# define COL_YELLOW "\033[0;33m"
# define COL_MAGENTA "\033[0;35m"
# define COL_DEFAULT "\033[0m"

# define EXCEPTION_HANDLER()            \
    catch (const std::exception &e)     \
    {\
        std::cerr << e.what() << '\n'; \
    }\

# define ERR_MSG_NoExpression        COL_RED "Error: no RPN expression." COL_DEFAULT
# define ERR_MSG_ToManyArgs         COL_RED "Error: Too many args." COL_DEFAULT
# define CHARS_WHITESPACE ("\n\t\v\f\r ")

class Rpn
{
    private:
        std::stack<int>  stkOperands;
        std::stringstream   ss;
        std::string         tmpExpStr;
        std::string         tokenStr;
        std::string::size_type  idx;
        int a;
        int b;

        Rpn( void );
        Rpn &operator=( Rpn const &rhs );
        bool        getToken(void);
        void        evaluate(void);

    public:
        Rpn( std::string const &expStr );
        ~Rpn( void );

};

#endif // RPH_HPP