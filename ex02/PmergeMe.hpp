
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
# include <cstring>
# include <ctime>
# include <algorithm>

# define COUT std::cout
# define ENDL std::endl
# define COL_BLUE       "\033[0;34m"
# define COL_RED        "\033[0;31m"
# define COL_YELLOW     "\033[0;33m"
# define COL_MAGENTA    "\033[0;35m"
# define COL_DEFAULT    "\033[0m"

# define ERR_MSG_NoExpression       COL_RED "Error: no sequence found." COL_DEFAULT
# define ERR_MSG_ToManyArgs         COL_RED "Error: Too many args." COL_DEFAULT
# define STATE_BEFORE ("before: ")
# define STATE_AFTER ("after: ")
# define MSG_TIME_1 ("Time to process a range of ")
# define MSG_TIME_2 (" elements with std::[..] : ")
# define MSG_TIME_3 (" us")
# define CHARS_WHITESPACE ("\n\t\v\f\r ")
# define INSERT_SORT_THRESHOLD (10)
# define SEQ_DISPLAY_RANGE (20)


/* Function Macros */
# define EXCEPTION_HANDLER()            \
    catch (const std::exception &e)     \
    {\
        std::cerr << e.what() << '\n'; \
    }\


#define SHOW_TIME(size,time) \
    {\
        COUT << MSG_TIME_1 << size << MSG_TIME_2 << time << MSG_TIME_3 << ENDL; \
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

typedef std::vector<int unsigned> tSeqVec;
typedef std::list<int unsigned> tSeqList;

class  PmergeMe
{
    private:
        tSeqVec     seqVec;
        tSeqList    seqList;
        clock_t     timeStartL;
        clock_t     timeStartV;
        clock_t     timeEndL;
        clock_t     timeEndV;
        std::list<int unsigned>::iterator   it_L;
        std::vector<int unsigned>::iterator it_V;
        
        PmergeMe(void);
        PmergeMe(PmergeMe const &obj);
        PmergeMe &operator=(PmergeMe const &obj);

        void showSequence(t_eSeq seqType, std::string const &seqStateStr);
        void showTime(t_eSeq seqType);
        clock_t computeTime(t_eSeq seqType);
        void insertionSortList(tSeqList &dataList);
        void insertionSortVector(tSeqVec &dataVector);
        void mergeInsertSortList(tSeqList dataList);
        void mergeInsertSortVector(tSeqVec &data);
        void mergeVector(tSeqVec &dataL, tSeqVec &dataR, tSeqVec &data);

    public:
        PmergeMe(char const *fp);
        ~PmergeMe(void);
};

#endif //PMERGEME_HPP
