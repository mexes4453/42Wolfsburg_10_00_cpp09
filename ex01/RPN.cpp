/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:04:46 by cudoh             #+#    #+#             */
/*   Updated: 2023/06/11 21:04:46 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

Rpn::Rpn( void ){}


Rpn::Rpn( std::string const &expStr ) : tmpExpStr(""), tokenStr(""), idx(0)
{
    ss.str( expStr );
    tmpExpStr = ss.str();

    while (getToken())
    {
    }

}


Rpn::~Rpn( void ){}


bool Rpn::getToken(void)
{
    bool    result = false;

    if (tmpExpStr.size() == 0)
        goto end;
    tokenStr.clear();

    idx = tmpExpStr.find_first_not_of(CHARS_WHITESPACE);
    if (idx != std::string::npos)
    {
        tmpExpStr = tmpExpStr.substr(idx);
        idx = tmpExpStr.find_first_of(CHARS_WHITESPACE);
        if (idx != std::string::npos)
        {
            tokenStr = tmpExpStr.substr(0, idx);
            tmpExpStr = tmpExpStr.substr(idx + 1);
            result = true;
        }
        else
        {
            if (tmpExpStr.size() > 0)
            {
                tokenStr = tmpExpStr;
                result = true;
                tmpExpStr.clear();
            }
        }
    }

#ifdef _DEBUG_
        COUT << "getToken : tokenStr -> " << tokenStr << ENDL;
#endif
end:
    return (result);
}