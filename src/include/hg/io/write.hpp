#ifndef HG_WRITE_HPP
#define HG_WRITE_HPP

#include <fstream>
#include <stdio.h>

namespace hg {
    namespace io {
        inline bool Write(char *&p, char *&o, unsigned int *&os){
            std::ofstream fo(p);
            if(!fo){ printf("error opening '%s'\n", p); return false; }

            for(unsigned int i = 0; i < *os; i++){ fo << o[i]; }
            fo.close();

            return true;
        }
    }
}

#endif //HG_WRITE_HPP