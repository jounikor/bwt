/**
 * Haven't gotten around making this into a class yet..
 *
 *
 *
 */



#include <iostream>
#include <new>
#include <cstdio>
#include <cstring>
#include <cinttypes>

namespace local {
    /**
     * \param L   BWT last output string.
     * \param T   Original text string returned here.
     * \paran len Length of T and L.
     * \param idx Index of the original string in L.
     * \return none.
     */
    
    static void ibwt( const char* L, char* T, int len, int idx ) {
        int n,i;
        
        int* K = new int[256];      // per character count
        int* C = new int[len];      // cumulative count of L[n] on pos L+n
        int* M = new int[256];      // start pos for each char in sorted L

        // Our character counts..

        ::memset(K,0,sizeof(int)*256);

        // Count characters.. and build C
        for (n = 0; n < len; n++) {
            C[n] = K[L[n]];
            K[L[n]]++;
        }

        // Build M
        for (i = n = 0; n < 256; n++) {
            M[n] = i;
            i += K[n];
        }

        // And reconstruct T.. traverse L in reverse order i.e.,
        // starting from the last symbol of the original string
        // pointed by the idx

        for (n = len-1; n >= 0; n--) {
            T[n] = L[idx];
            idx = C[idx] + M[L[idx]];
        }

        // clean up

        delete[] K;
        delete[] C;
        delete[] M;
    }




};


using namespace std;


int main( int argc, char** argv ) {

    int l, i;

    if (argc < 3) {
        std::cerr << "usage: " << argv[1] << " bwtstring index" << std::endl;
        return 0;
    }

    const char* s = argv[1];
    i = ::strtol(argv[2],NULL,10);
    l = ::strlen(s);
    char* t = new char[l+1];
    t[l] = '\0';

    local::ibwt( s, t, l, i );

    cout << " bwt:" << s << endl;
    cout << "ibwt:" << t << endl;
    delete t;

    return 0;
}



