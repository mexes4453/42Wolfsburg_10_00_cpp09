
#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <list>
# include <vector>
# include <iostream>
# include <stdexcept>
# include <fstream>
# include <cstdlib>
# include <sstream>
# include <string>
# include <time.h>
# include <iomanip>

# define COUT std::cout
# define ENDL std::endl
# define COL_BLUE       "\033[0;34m"
# define COL_RED        "\033[0;31m"
# define COL_YELLOW     "\033[0;33m"
# define COL_MAGENTA    "\033[0;35m"
# define COL_DEFAULT    "\033[0m"

# define ERR_MSG_NoExpression       COL_RED "Error: no sequence found." COL_DEFAULT
# define ERR_MSG_InvalidInput       COL_RED "Error" COL_DEFAULT
# define ERR_MSG_IncompleteSort     COL_RED "Error: incomplete sort" COL_DEFAULT
# define STATE_BEFORE ("before:   ")
# define STATE_AFTER ("after:    ")
# define MSG_TIME_1 ("Time to process a range of ")
# define MSG_TIME_2 (" elements with std::[..] : ")
# define MSG_TIME_3 (" us")
# define CHARS_WHITESPACE ("\n\t\v\f\r ")
# define INSERT_SORT_THRESHOLD (10)
# define SEQ_DISPLAY_RANGE (5)
# define TIME_MS (1000.0L)
# define TIME_US (1000000.0L)
# define TIME_NS (1000000000.0L)

/* Function Macros */
# define EXCEPTION_HANDLER()            \
    catch (const std::exception &e)    \
    {\
        std::cerr << e.what() << '\n'; \
    }\


#define SHOW_SEQUENCE(seq,iter) \
    {\
        iter = seq.begin(); \
        if (seq.size() > SEQ_DISPLAY_RANGE) \
        {\
            for (int unsigned x=0; x < SEQ_DISPLAY_RANGE; x++) \
            {\
                COUT << *iter << " "; \
                ++iter; \
            }\
            COUT << "[...]"; \
        }\
        else \
        {\
            while (iter != seq.end()) \
            {\
                COUT << *iter << " "; \
                ++iter; \
            }\
        }\
    }\


typedef enum    eSeq
{
    enSeqList = 1,
    enSeqVector
}   t_eSeq;

typedef enum    eTimeUnit
{
    enTimeUnit_MS,
    enTimeUnit_US,
    enTimeUnit_NS,
    enTimeUnit_S,
}   t_eTimeUnit;

typedef std::vector<int unsigned> tSeqVec;
typedef std::list<int unsigned> tSeqList;
typedef struct timespec t_time;

class  PmergeMe
{
    private:
        tSeqVec                 seqVec;
        tSeqList                seqList;
        tSeqList                seqListRaw;
        t_time                  timeStartL;
        t_time                  timeStartV;
        t_time                  timeEndL;
        t_time                  timeEndV;
        tSeqList::iterator      it_L;
        tSeqVec::iterator       it_V;
        std::stringstream       ss;
        std::string             tmpExpStr;
        std::string             tokenStr;
        std::string::size_type  idx;
        
        PmergeMe(void);
        PmergeMe(PmergeMe const &obj);
        PmergeMe &operator=(PmergeMe const &obj);

        void            showSequence(t_eSeq seqType, std::string const &seqStateStr);
        void            showSequenceList(tSeqList &data, std::string const &seqStateStr);
        void            showTime(t_time &timeStart, t_time &timeEnd);
        long double     computeTimeDiff(t_time &timeStart, t_time &timeEnd, t_eTimeUnit unit);
        void            insertionSortList(tSeqList &dataList);
        void            insertionSortVector(tSeqVec &dataVector);
        void            mergeInsertSortList(tSeqList &data);
        void            mergeInsertSortVector(tSeqVec &data);
        void            mergeVector(tSeqVec &dataL, tSeqVec &dataR, tSeqVec &data);
        void            mergeList(tSeqList &dataL, tSeqList &dataR, tSeqList &data);
        bool            getToken(void);
        int unsigned    convertTokenToInt(void);
        bool            serializeArgsList(int argc, char *argv[], tSeqList &seq);
        bool            serializeArgsVector(int argc, char *argv[], tSeqVec &seq);
        void            sortVector(int argc, char *argv[]);
        void            sortList(int argc, char *argv[]);
        bool            verifySort(void);

    public:
        PmergeMe(int argc, char *argv[]);
        ~PmergeMe(void);
};

#endif //PMERGEME_HPP
