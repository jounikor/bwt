/**
 * \file bwt.h
 * \brief Burrows-Wheeler Transform definitions.
 *
 * This class implements a memory efficient BWT algorithm.
 *
 * \author Jouni korhonen 
 * \email jouni.korhonen@iki.fi
 * \version 0.2
 * \copyright (c) 2016 I have no idea.
 * \warning This code base is just for self education purposes.
 *
 */

#include <vector>
#include <exception>
#include <cstring>
#include <cstdlib>

/**
 * \class bwt
 * \brief Base class for Burrows Wheeler Transform
 */

class bwt {
    int m_len;              ///< Length of the input string
    const char* m_T;        ///< Pointer to the input string
    std::vector<int> m_SA;  ///< Work array for the input string
#if 1   // for non-C++11 compilers..
    bwt& operator=(bwt &b) { return *this; }
    const bwt& operator=(const bwt &b) { return *this; }
#endif
public:
    virtual bool operator()( int, int ) const;
    int operator[](int) const;
    virtual ~bwt();
    bwt( const char* const, int );
    bwt( const bwt&  );
    bwt();
   
#if 0   // requires C++11 and I kind of suck at it..
    bwt& operator=( bwt& ) = delete;
    bwt& operator=( const bwt& ) = delete;
#endif
    void sort( const char* const, int ) throw (std::invalid_argument);
    void sort( void ) throw (std::invalid_argument);
    int getOriginalString( void ) const;
};

