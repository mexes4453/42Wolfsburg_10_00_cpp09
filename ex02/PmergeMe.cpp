
#include "PmergeMe.hpp"


PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(char const *fp)
{
#ifdef _DEBUG_
    COUT << "PmergeMe_Constructor: " << fp << ENDL;
    seqVec.push_back(2);
    seqVec.push_back(3);
    seqVec.push_back(4);
    seqVec.push_back(5);
    seqVec.push_back(6);
    seqVec.push_back(7);
    seqVec.push_back(8);
    seqVec.push_back(9);
    seqVec.push_back(1);
    seqVec.push_back(0);
    seqVec.push_back(9);
    seqVec.push_back(8);
    seqVec.push_back(5);
    seqList.push_back(8);
    seqList.push_back(5);
    seqList.push_back(9);
    seqList.push_back(2);
    showTime(enSeqList);
    showTime(enSeqVector);
    showSequence(enSeqList, STATE_AFTER);
    showSequence(enSeqVector, STATE_BEFORE);
#endif

}

PmergeMe::~PmergeMe(void){}


void    PmergeMe::showSequence(t_eSeq seqType, std::string const &seqStateStr)
{
    COUT << seqStateStr;
    switch (seqType)
    {
        case enSeqList:
        {
            SHOW_SEQUENCE(seqList,it_L);
            break ;
        }
        case enSeqVector:
        {
            SHOW_SEQUENCE(seqVec,it_V);
            break ;
        }
        default:
        {
            // do nothing
            break ;
        }
    }
    COUT << ENDL;
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



void    insertionSortList(tSeqList dataList)
{
    unsigned int idx = 1;
    tSeqList::iterator it = dataList.begin();




    
    
}