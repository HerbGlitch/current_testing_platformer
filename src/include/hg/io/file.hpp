#ifndef HG_FILE_HPP
#define HG_FILE_HPP

#include <fstream>
#include <stdio.h>

namespace hg {
    namespace io {
        inline char *File(char *path, unsigned int *&size){
            #ifdef HG_DEBUG
                printf("%s\n", path);
            #endif

            std::ifstream fo(path, std::ios::in | std::ios::binary | std::ios::ate); // open the file
            if(!fo){
                #ifdef HG_DEBUG
                    printf("error opening '%s'\n", path);
                #endif

                size = new unsigned int (0);
                return new char[1]{'\0'}; // error handling for if can't open file
            } 

            size = new unsigned int(fo.tellg()); // get size then allocate in memory
            char *fd = new char[*size + 1];

            fo.seekg(0, std::ios::beg); // load in file
            fo.read(fd, *size);
            fo.close();
            fd[*size] = '\0';

            return fd;
        }
    }
}

#endif //HG_FILE_HPP