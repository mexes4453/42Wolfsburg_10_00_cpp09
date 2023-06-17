
#include "PmergeMe.hpp"


PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(char const *fp)
{
#ifdef _DEBUG_
    COUT << "PmergeMe_Constructor: " << fp << ENDL;
    seqVec.push_back(2);
    seqList.push_back(8);
    showTime(enSeqList);
    showTime(enSeqVector);
    showSequence(enSeqList, "after");
#endif

}

PmergeMe::~PmergeMe(void){}


void    PmergeMe::showSequence(t_eSeq seqType, std::string const &seqStateStr)
{
    COUT << seqStateStr << ": ";
    switch (seqType)
    {
        case enSeqList:
        {
            it_L = seqList.begin();
            if (seqList.size() > SEQ_DISPLAY_RANGE)
            {
               for (int unsigned x=0; x < SEQ_DISPLAY_RANGE; x++)
               {
                    COUT << *it_L << " ";
                    ++it_L;
               }
            }
            else
            {
                while (it_L != seqList.end())
                {
                    COUT << *it_L << " ";
                    ++it_L;
                }
            }
            COUT << ENDL;
            break ;
        }
        case enSeqVector:
        {
            break ;
        }
    }
}

clock_t    PmergeMe::computeTime(t_eSeq seqType)
{
#ifdef _DEBUG_
    COUT << "computeTime: seqType-> " << seqType << ENDL;
#endif
    return (45);
}

void    PmergeMe::showTime(t_eSeq seqType)
{
    switch (seqType)
    {
        case enSeqList:
        {
            SHOW_TIME(seqList.size(), computeTime(enSeqList));
            break ;
        }
        case enSeqVector:
        {
            SHOW_TIME(seqVec.size(), computeTime(enSeqVector));
            break ;
        }
        default:
        {
            // do nothing
            break ;
        }
    }
}