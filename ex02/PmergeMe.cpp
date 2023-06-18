
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
    seqList.push_back(3);
    seqList.push_back(9);
    seqList.push_back(2);
    showTime(enSeqList);
    showTime(enSeqVector);
    showSequence(enSeqList, STATE_BEFORE);
    showSequence(enSeqVector, STATE_BEFORE);
    insertionSortList(seqList);
    showSequence(enSeqList, STATE_AFTER);
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



void    PmergeMe::insertionSortList(tSeqList &dataList)
{
    int unsigned        idx = 1;
    tSeqList::iterator  it_L = dataList.begin();
    tSeqList::iterator  it_R = dataList.begin();
    
    ++it_R;
    while (it_R != dataList.end())
    {
        it_L = dataList.begin();
        while ((it_L != dataList.end()) && (*it_R > *it_L))
        {
            ++it_L;
        }
#ifdef _DEBUG_
        COUT << "Before splice: " << *it_R << ENDL;
#endif
        dataList.splice(it_L, dataList, it_R);
#ifdef _DEBUG_
        COUT << "After splice: " << *it_R << ENDL;
#endif
        ++idx;
        it_R = dataList.begin();
        std::advance(it_R, idx);
    }
}

void    PmergeMe::insertionSortVector(tSeqVec &dataVector)
{
    int unsigned        idx = 1;
    tSeqVec::iterator  it_L = dataVector.begin();
    tSeqVec::iterator  it_R = dataVector.begin();
    
    ++it_R;
    while (it_R != dataVector.end())
    {
        it_L = dataVector.begin();
        while ((it_L != dataVector.end()) && (*it_R > *it_L))
        {
            ++it_L;
        }
#ifdef _DEBUG_
        COUT << "Before splice: " << *it_R << ENDL;
#endif
        dataVector.insert(it_L, *it_R);
        
#ifdef _DEBUG_
        COUT << "After splice: " << *it_R << ENDL;
#endif
        ++idx;
        it_R = dataVector.begin();
        std::advance(it_R, idx);
    }

}