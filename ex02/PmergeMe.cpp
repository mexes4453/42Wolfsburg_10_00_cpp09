
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
    //insertionSortVector(seqVec);
    showSequence(enSeqList, STATE_AFTER);
    showSequence(enSeqVector, STATE_AFTER);

    tSeqVec rVector(seqVec);
    tSeqVec rData(24, 0);
    //insertionSortVector(rVector);
    mergeVector(seqVec, rVector, rData);
    mergeInsertSortVector(rData);
    tSeqVec::iterator it = rData.begin();
    while ( it != rData.end())
    {
        COUT << *it << " ";
        ++it;
    }
    COUT << ENDL;
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
        COUT << "insertionSortList: Before splice: " << *it_R << ENDL;
#endif
        dataList.splice(it_L, dataList, it_R);
#ifdef _DEBUG_
        COUT << "insertionSortList: After splice: " << *it_R << ENDL;
#endif
        ++idx;
        it_R = dataList.begin();
        std::advance(it_R, idx);
    }
}

void    PmergeMe::insertionSortVector(tSeqVec &dataVector)
{
    tSeqVec::iterator  it_L = dataVector.begin();
    tSeqVec::iterator  it_R = dataVector.begin();
    int unsigned       tmpNbr = 0;
    
    ++it_R;
    while (it_R != dataVector.end())
    {
        it_L = it_R;
        tmpNbr = *it_R;
#ifdef _DEBUG_
        COUT << "insertionSortVector: unsorted idx value -> " << *it_R << ENDL;
#endif
        while ((it_L != dataVector.begin()) && (*(it_L - 1) > tmpNbr))
        {
#ifdef _DEBUG_
        COUT << "insertionSortVector: *it_L value -> " << *it_L << ENDL;
        COUT << "insertionSortVector: *it_L - 1 value -> " << *(it_L - 1) << ENDL;
#endif            
            *it_L = *(it_L - 1);
            --it_L;
        }
        // check if left interator moved to the left
        if (it_L != it_R)
        {
            *it_L = tmpNbr;
        }
        ++it_R;
    }
}


void PmergeMe::mergeVector(tSeqVec &dataL, tSeqVec &dataR, tSeqVec &data)
{
    tSeqVec::iterator  itL=dataL.begin();
    tSeqVec::iterator  itR=dataR.begin();
    tSeqVec::iterator  it=data.begin();

    while (itL != dataL.end() && itR != dataR.end())
    {
        if (*itL < *itR)
        {
            *it = *itL;
            ++itL;
        }
        else
        {
            *it = *itR;
            ++itR;
        }
        ++it;
    }
    // if right data is at end, move remaining data in left data
    while (itL != dataL.end())
    {
        *(it++) = *(itL++);
    }

    // if left data is at end, move remaining data in right data
    while (itR != dataR.end())
    {
        *(it++) = *(itR++);
    }
}

void PmergeMe::mergeInsertSortVector(tSeqVec &data)
{
    tSeqVec dataL (data.begin(), (data.begin() + (data.size() / 2)));
    tSeqVec dataR ((data.begin() + (data.size() / 2)), data.end());

    if (data.size() < 2 ) 
    {
        goto end;
    }
    else if (data.size() <= INSERT_SORT_THRESHOLD)
    {
        insertionSortVector(data);
        goto end;
    }

    mergeInsertSortVector(dataL);
    mergeInsertSortVector(dataR);
    mergeVector(dataL, dataR, data);
end:
    return ;
}



