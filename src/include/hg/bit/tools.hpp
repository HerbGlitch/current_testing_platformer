#ifndef HG_BIT_TOOLS_HPP
#define HG_BIT_TOOLS_HPP

#include <stdio.h>

namespace hg {
    const int BYTE = 8;

    namespace bit {
        inline unsigned short gethex(char *p); //defined here for cstorgbhex

        inline unsigned int ptoui(char *p){  return ((0xff & *(p + 3)) << 24 | (0xff & *(p + 2)) << 16 | (0xff & *(p + 1)) << 8 |(0xff & *p)); } // pointer to unsigned int
        inline unsigned int ptopx(char *p){  return ((0xff & *(p + 2)) << 16 | (0xff & *(p + 1)) << 8  | (0xff & *p)); } // pointer to px
        inline unsigned char ptous(char *p){ return ((0xff & *(p + 1)) << 8  | (0xff & *p)); } // pointer to unsigned short
        inline unsigned int cstorgbhex(char *p){ return (gethex(p) << 20 | gethex(p + 1) << 16 | gethex(p + 2) << 12 | gethex(p + 3) << 8 | gethex(p + 4) << 4 | gethex(p + 5)); }

        inline bool isCRLF(char *p){ return (*p == char(0x0d) && *(p + 1) == '\n'); } //for windows

        inline unsigned short *getClosestBit(unsigned int *b){
            for(unsigned short i = 0; i < sizeof(unsigned int) * BYTE; i++){ if((unsigned int)(1 << i) > (*b - 1)){ return new unsigned short(i); }}
            return new unsigned short(~0);
        }

        inline unsigned short gethex(char *p){
            if(*p >= '0' && *p <= '9'){ return *p - '0'; }
            if(*p >= 'a' && *p <= 'f'){ return *p - 'a' + 10; }
            printf("Error, could not get hex from char '%c' char hex '%x' at location: %p", *p, *p, p);
            return ~(unsigned short)0;
        }

        inline unsigned char gethexfrombinary(char *p){
            if(*p >= 0 && *p <= 9){ return '0' + *p; }
            if(*p >= 10 && *p <= 15){ return 'a' + (*p - 10); }
            printf("Error, could not get hex from char '%x' char hex '%x' at location: %p", *p, *p, p);
            return ~(unsigned short)0;
        }

        inline bool getValAtInv(char *arr, unsigned int *index, unsigned short *currBit){
            bool temp = ((unsigned char)*(arr + *index) >> *currBit) & 1 == 1;
            ++*currBit;
            if(*currBit >= sizeof(char) * BYTE){
                ++*index;
                *currBit = 0;
            }
            return temp;
        }

        inline bool getValAt(char *arr, unsigned int *index, unsigned short *currBit){
            bool temp = ((unsigned char)*(arr + *index) >> ((sizeof(char) * BYTE) - 1) - *currBit) & 1 == 1;
            ++*currBit;
            if(*currBit >= sizeof(char) * BYTE){
                ++*index;
                *currBit = 0;
            }
            return temp;
        }

        inline bool printCharHex(char *p){
            char c = ((char)*p & 0x00f0) >> 4;
            printf("%c", gethexfrombinary(&c));

            c = (char)(*p & 0x000f);
            printf("%c", gethexfrombinary(&c));
        }
    }
}

#endif //HG_BIT_TOOLS_HPP