/**
 * \file bwt.cpp
 * \brief Burrows Wheeler Transform implementation
 *
 * This class implements a memory efficient BWT algorithm.
 *
 * \author Jouni korhonen <jouni.korhonen@iki.fi>
 * \version 0.2
 *
 * This class implements BWT transform. Due its "self education" purpose 
 * the implementation naively mixed old C++ and C++11 syntax within
 * annoying #if statements.. sorry
 */

#include <iostream>
#include <new>
#include <algorithm>

#include <cstring>
#include <cstdlib>

#include "bwt.h"

/**
 * \brief Overload the operator() for sorting purposes.
 * 
 * \param[in] a BWT array element left index. 
 * \param[in] b BWT array element right index.
 *
 * \return True if BWT[a] < BWT[b], otherwise false.
 */
bool bwt::operator()( int a, int b ) const
{
    for (int n = 0; n < m_len; n++) {
        if (m_T[a] != m_T[b]) {
            return m_T[a] < m_T[b];
        }
        a++, b++;

        // if m_len is always power of two the bounds checking
        // could be optimized nicely to an AND/mask operation..
        //
        // a = (a + 1) & m_mask; etc..

        if (a >= m_len) {
            a = 0;
        }
        if (b >= m_len) {
            b = 0;
        }
    }
    // should never get here..
    return false;
}

/**
 * \brief ..
 *
 *
 *
 */
int bwt::getOriginalString( void ) const
{
    int n;

    for (n = 0; n < m_len; n++) {
        if (m_SA.at(n) == 0) {
            return n;
        }
    }
    return -1;
}

/**
 * \brief Return the character from the sorted BWT array at a given index.
 * \param i Index to the sorted BWT array.
 * \return The value of the BWT array at a given index.
 */
int bwt::operator[]( int i ) const
{
    return m_SA.at(i);
}

/**
 * \brief Destructor..
 *
 *
 */
bwt::~bwt() {
}

/**
 * \brief Copy constructor.
 * \param b The instatiated object to copy from.
 *
 */
bwt::bwt( const bwt& b )
{
    m_T = b.m_T;
    m_len = b.m_len;
    m_SA.clear();
    std::cerr << "bwt( const bwt& )" << std::endl;
}

/**
 * \brief Constructor
 * \param[in] T A pointer to the input array of characters. 
 * \param[in] len The length of array T.
 */
bwt::bwt( const char* const T, int len) {
    m_T = T;
    m_len = len;
    m_SA.clear();
    std::cerr << "bwt()" << std::endl;
}

/**
 * \brief Contrutor that initialized a NULL BWT string.
 *
 */
bwt::bwt()
{
    m_T = NULL;
    m_len = 0;
}

/**
 * \brief Buildin BWT sorting method. Since this is a virtual function
 *   one can override it easily in derived classes.
 * 
 *
 */
void bwt::sort( void ) throw (std::invalid_argument)
{
    int n = 0;

    // Check if we actually have 
    if (m_T == NULL) {
        throw std::invalid_argument("NULL bwt string");
    }

    m_SA.clear();

    for (n = 0; n < m_len; n++) {
        m_SA.push_back( n );
    }

#if 1
    std::stable_sort( m_SA.begin(),m_SA.end(),*this );
#else
    // Ok this is a bad idea.. C++11 lamda functions..
    std::stable_sort( m_SA.begin(),m_SA.end(), 
        [this](int a, int b) -> bool {
        int n;
        
        for (n = 0; n < this->m_len; n++) {
            if (this->m_T[a] != this->m_T[b]) {
                return this->m_T[a] < this->m_T[b];
            }
            a++, b++;

            if (a >= this->m_len) {
                a = 0;
            }
            if (b >= this->m_len) {
                b = 0;
            }
        }
        return false;
    });
#endif
}

void bwt::sort( const char* const t, int l ) throw (std::invalid_argument)
{
    m_T = t;
    m_len = l;
    sort();
}

//
// Test main() for the BWT..
//

int main( int argc, char** argv )
{

    char str[] = "SIX.MIXED.PIXIES.SIFT.SIXTY.PIXIE.DUST.BOXES";
    //char str[] = "mississippi";
    //char str[] = "abradacabra";
    int len = strlen(str);
    int n;

    bwt myBwt( str, len );
    myBwt.sort();

    std::cout << "Count\tIndex\tFirst\tLast" << std::endl;
#if 1
    for (n = 0; n < len; n++) {
        std::cout   << n << ":\t" << myBwt[n] << "\t"
                    << str[myBwt[n]] << "\t" 
                    << str[(myBwt[n]+len-1)%len] << std::endl;
    }
#else
    for (n = 0; n < len; n++) {
        std::cout << str[(myBwt[n]+len-1)%len]; 
    }
#endif
    std::cout << std::endl << "Original string index: " 
              << myBwt.getOriginalString() << " ("
              << len << ")" << std::endl;


    myBwt.sort( str, len );
    std::cout << "Count\tIndex\tFirst\tLast" << std::endl;
    for (n = 0; n < len; n++) {
        std::cout   << n << ":\t" << myBwt[n] << "\t"
                    << str[myBwt[n]] << "\t" 
                    << str[(myBwt[n]+len-1)%len] << std::endl;
    }

#if 0
    try {
        myBwt.sort( NULL, len );
    }
    catch (std::exception& e) {
        std::cerr << "Bad argument(s) given to bwt bwt:sort()" << std::endl;
        std::cerr << e.what() << std::endl;
    }
#endif
    return 0;
}
