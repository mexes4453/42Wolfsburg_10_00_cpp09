
#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(int argc, char *argv[])
{

    if (serializeArgsList(argc, argv, seqListRaw))          // serialize args into container
    {
        sortList(argc, argv);                               // serialize and sort list container
        sortVector(argc, argv);                             // serialize and sort vector container
        if (verifySort())                                   // check that both container sort is ok
        {
            showSequenceList(seqListRaw, STATE_BEFORE);     // show sequence before sort ops
            showSequenceList(seqList, STATE_AFTER);         // show sequence after sort ops
            showTime(timeStartL, timeEndL);                 // show time required by list
            showTime(timeStartV, timeEndV);                 // show time required by vector
        }
    }
#ifdef _DEBUG_
    COUT << "PmergeMe_Constructor: " << fp << ENDL;
    showSequence(enSeqList, STATE_BEFORE);
    showSequence(enSeqVector, STATE_BEFORE);
    showSequence(enSeqList, STATE_AFTER);
    showSequence(enSeqVector, STATE_AFTER);

    tSeqVec rVector(seqVec);
    tSeqVec rData(24, 0);
    mergeVector(seqVec, rVector, rData);
    mergeInsertSortVector(rData);
    mergeInsertSortVector(rData);
    mergeInsertSortVector(seqVec);
    mergeInsertSortList(seqList);
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


double long PmergeMe::computeTimeDiff(t_time &timeStart, t_time &timeEnd, t_eTimeUnit unit)
{

    long long start = timeStart.tv_nsec + (timeStart.tv_sec * TIME_NS);
    long long end = timeEnd.tv_nsec + (timeEnd.tv_sec * TIME_NS);
    double long diff = (end - start) / TIME_NS;                     // computed in sec 

    switch (unit)
    {
        case enTimeUnit_MS:
        {
            diff *= TIME_MS;
            break ;
        }
        case enTimeUnit_US:
        {
            diff *= TIME_US;
            break ;
        }
        case enTimeUnit_NS:
        {
            diff *= TIME_NS;
            break ;
        }
        default:
        {
            // returns the computed difference in sec
            break ;
        }
    }
    return (diff);
}

void    PmergeMe::showTime(t_time &timeStart, t_time &timeEnd)
{
    COUT << MSG_TIME_1 << seqListRaw.size()
         << MSG_TIME_2 << std::setprecision(5) 
         << computeTimeDiff(timeStart, timeEnd, enTimeUnit_MS)
         << MSG_TIME_3 << ENDL;
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

void PmergeMe::mergeList(tSeqList &dataL, tSeqList &dataR, tSeqList &data)
{
    tSeqList::iterator  itL=dataL.begin();
    tSeqList::iterator  itR=dataR.begin();
    tSeqList::iterator  it=data.begin();

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
#ifdef _DEBUG_
    COUT << "mergeInsertSortVector: dataVector-> ";
    showSequence(enSeqVector, STATE_AFTER);
#endif
    return ;
}


void PmergeMe::mergeInsertSortList(tSeqList &data)
{
    tSeqList::iterator it = data.begin();
    std::advance(it, (data.size() / 2));
    tSeqList dataL (data.begin(), it);
    it = data.begin();
    std::advance(it, (data.size() / 2));
    tSeqList dataR (it, data.end());

    if (data.size() < 2 ) 
    {
        goto end;
    }
    else if (data.size() <= INSERT_SORT_THRESHOLD)
    {
        insertionSortList(data);
        goto end;
    }

    mergeInsertSortList(dataL);
    mergeInsertSortList(dataR);
    mergeList(dataL, dataR, data);
end:
#ifdef _DEBUG_
    COUT << "mergeInsertSortList: dataList-> ";
    showSequence(enSeqList, STATE_AFTER);
#endif
    return ;
}

bool PmergeMe::getToken(void)
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


int unsigned  PmergeMe::convertTokenToInt(void)
{
    int unsigned nbr = 0;
    std::stringstream   ss(tokenStr);
    std::ostringstream  oss;

    if (ss >> nbr)
    {
        oss << nbr;
#ifdef _DEBUG_
        COUT << tokenStr << " : " << oss.str() << " : " << nbr << ENDL;
#endif
        if (oss.str().size() != tokenStr.size())
        {
            throw std::runtime_error(ERR_MSG_InvalidInput);
        }
    }
    else
    {
        throw std::runtime_error(ERR_MSG_InvalidInput);
    }
    return (nbr);
}

void    PmergeMe::sortVector(int argc, char *argv[])
{
    try
    {
        
        clock_gettime(CLOCK_MONOTONIC, &timeStartV);    // Record start time
        serializeArgsVector( argc, argv, seqVec );      // Convert args to int & store in container
        mergeInsertSortVector(seqVec);                  // Perform sort on vector container
        clock_gettime(CLOCK_MONOTONIC, &timeEndV);      // Record stop time
    }
    EXCEPTION_HANDLER();

}


void    PmergeMe::sortList(int argc, char *argv[])
{
    try
    {
        clock_gettime(CLOCK_MONOTONIC, &timeStartL);    // Record start time
        serializeArgsList( argc, argv, seqList);        // Convert args to int & store in List
        mergeInsertSortList(seqList);                   // Perform sort on list container
        clock_gettime(CLOCK_MONOTONIC, &timeEndL);      // Record stop time

    }
    EXCEPTION_HANDLER();
}

 bool    PmergeMe::serializeArgsList(int argc, char *argv[], tSeqList &seq)
 {
    int                 idx = 1;
    bool                result = false;
    std::ostringstream  oss;

    try
    {
        seq.clear();
        while (idx < argc)
        {
            oss.clear();
            oss.str( argv[idx] );
            tmpExpStr = oss.str();
#ifdef _DEBUG_
            COUT << argv[idx] << ENDL;
            COUT << tmpExpStr << ENDL;
            tmpExpStr = argv[idx];
#endif
            while (getToken())
            {
                seq.push_back(convertTokenToInt());
            }
            idx++;
        }
        result = true;
#ifdef _DEBUG_
        showSequenceList(seq, STATE_BEFORE);
#endif
    }
    EXCEPTION_HANDLER();
#ifdef _DEBUG_
    COUT << idx << " : " << argv[idx] << ENDL;
#endif
    return (result);
 }


 bool    PmergeMe::serializeArgsVector(int argc, char *argv[], tSeqVec &seq)
 {
    int                 idx = 1;
    bool                result = false;
    std::ostringstream  oss;

    try
    {
        seq.clear();
        while (idx < argc)
        {
            oss.clear();
            oss.str( argv[idx] );
            tmpExpStr = oss.str();
#ifdef _DEBUG_
            COUT << argv[idx] << ENDL;
            COUT << tmpExpStr << ENDL;
            tmpExpStr = argv[idx];
#endif
            while (getToken())
            {
                seq.push_back(convertTokenToInt());
            }
            idx++;
        }
        result = true;
#ifdef _DEBUG_
        showSequenceList(seq, STATE_BEFORE);
#endif
    }
    EXCEPTION_HANDLER();
#ifdef _DEBUG_
    COUT << idx << " : " << argv[idx] << ENDL;
#endif
    return (result);
 }


 void PmergeMe::showSequenceList(tSeqList &data, std::string const &seqStateStr)
 {
    it_L = data.begin();
    COUT << seqStateStr;

    if (data.size() > SEQ_DISPLAY_RANGE)
    {
        for (int unsigned x = 0; x < SEQ_DISPLAY_RANGE; x++)
        {
            COUT << *it_L << " ";
            ++it_L;
        }
        COUT << "[...]";
    }
    else
    {
        while (it_L != data.end())
        {
            COUT << *it_L << " ";
            ++it_L;
        }
    }
    COUT << ENDL;
 }

bool            PmergeMe::verifySort(void)
{
    bool    result = false;

    it_L = seqList.begin();
    it_V = seqVec.begin();
    try
    {
        while (it_L != seqList.end())
        {
            if (*it_L != *it_V)
            {
                throw std::runtime_error(ERR_MSG_IncompleteSort);
            }
            ++it_L;
            ++it_V;
        }
        result = true;
    }
    EXCEPTION_HANDLER();
    return (result);
}