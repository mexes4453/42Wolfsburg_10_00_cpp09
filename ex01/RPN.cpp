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


Rpn::Rpn( std::string const &expStr ) : tmpExpStr(""), tokenStr(""), idx(0),
a(0), b(0)
{
    ss.str( expStr );
    tmpExpStr = ss.str();

    try
    {
        while (getToken())
        {
            if (tokenStr.size() != 1) throw std::runtime_error("Error");
            if (isdigit(tokenStr[0]))
            {
                stkOperands.push(tokenStr[0] - 0x30);
            }
            else // Sign found
            {
                if (stkOperands.size() >= 2)
                {
                    b = stkOperands.top();
                    stkOperands.pop();
                    a = stkOperands.top();
                    stkOperands.pop();
                    evaluate();
                }
                else
                {
                    throw std::runtime_error("Error");
                }
            }
        }
        if (stkOperands.size() != 1)
        {
            throw std::runtime_error("Error");
        }
        COUT << stkOperands.top() << ENDL;
    }
    EXCEPTION_HANDLER();
}


Rpn::~Rpn( void ){}


bool Rpn::getToken(void)
{
    bool    result = false;

    if (tmpExpStr.size() == 0)
        goto end;
    tokenStr.clear();

    // removing leading whitespaces
    idx = tmpExpStr.find_first_not_of(CHARS_WHITESPACE);
    if (idx != std::string::npos)
    {
        tmpExpStr = tmpExpStr.substr(idx);

        // removing trailing whitespaces
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

void    Rpn::evaluate(void)
{
    switch (tokenStr[0])
    {
        case '*':
        {
            stkOperands.push(a * b);
            break ;
        }
        case '-':
        {
            stkOperands.push(a - b);
            break ;
        }
        case '/':
        {
            stkOperands.push(a / b);
            break ;
        }
        case '+':
        {
            stkOperands.push(a + b);
            break ;
        }
        default:
        {
            throw std::runtime_error("Error: unknown operand");
            break;
        }
    }
}