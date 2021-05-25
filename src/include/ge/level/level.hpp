#ifndef GE_LEVEL_HPP
#define GE_LEVEL_HPP

#define GE_DEBUG

#include <hg/lib.hpp>
#include <stdio.h>
#include <string>

namespace ge {
    namespace level {
        struct Data {
            unsigned int width;
            unsigned int height;
            unsigned int *map;

            std::string *names;
            unsigned int namesSize;

            ~Data(){
                delete map;
                delete names;
            }
        };

        inline unsigned int getui(unsigned short &base, char *file, unsigned int *fileIndex, unsigned short *currBit){
            unsigned int final = 0;
            for(unsigned short i = 1; i <= base; i++){
                bool temp = (hg::bit::getValAt(file, fileIndex, currBit)? 1 : 0);
                final += (temp? 1 : 0) << (base - i);
            }

            return final;
        }

        inline Data *loadData(char *path){
            unsigned int *size;
            char *file = hg::io::File(path, size);

            unsigned int offset = 0;
            Data *data = new Data();

            data->width = hg::bit::ptoui(file);
            offset += 4;

            data->height = hg::bit::ptoui(file + offset);
            offset += 4;

            data->map = new unsigned int[data->width * data->height];

            unsigned short base = hg::bit::ptous(file + offset);
            offset += 2;

            data->namesSize = hg::bit::ptoui(file + offset);
            data->names = new std::string[data->namesSize];
            offset += 4;

            unsigned int overflow = hg::bit::ptoui(file + offset);
            offset += 4;

            #ifdef GE_DEBUG
                printf("w: %d, h: %d, b: %d, o: %u\n", data->width, data->height, (int)base, overflow);
            #endif


            for(unsigned int i = 0; i < data->namesSize; i++){
                std::string temp = "";
                for(; file[offset] != char(0); offset++){ temp += file[offset]; }
                temp += file[offset];
                offset++;

                data->names[i] = temp;
            }

            #ifdef GE_DEBUG
                printf("offset: %d\n", offset);
            #endif

            offset += (overflow == 0)? 0 : (sizeof(unsigned int) * hg::BYTE) - overflow; //todo: fix later

            unsigned short *currBit = new unsigned short(0x0);
            for(unsigned int i = 0; i < data->width * data->height; i++){
                data->map[i] = getui(base, file, &offset, currBit);
            }

            for(unsigned int i = 0; i < data->width * data->height; i++){ printf("%s ", data->names[data->map[i]].c_str()); }

            delete currBit;
            delete size;
            delete file;

            return data;
        }
    }
}

#endif //GE_LEVEL_HPP