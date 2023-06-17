/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:25:32 by cudoh             #+#    #+#             */
/*   Updated: 2023/05/21 17:25:32 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
    PmergeMe *merger;

    try
    {
        if (argc == 1)      // check if user did not provide argument
        {
            throw std::runtime_error(ERR_MSG_NoExpression);
        }
        else if (argc == 2) // check if user provided only one argument
        {
            merger = new PmergeMe(argv[1]);
            delete merger;
        }
        else                // user provided more than one argument
        {
            throw std::runtime_error(ERR_MSG_ToManyArgs);
        }
    }
    EXCEPTION_HANDLER();
    return (0);
}
