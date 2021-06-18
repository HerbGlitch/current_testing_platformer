#ifndef GE_LEVEL_HPP
#define GE_LEVEL_HPP

#define GE_DEBUG

#include <hg/lib.hpp>
#include <stdio.h>
#include <string>

namespace ge {
    namespace level {
        class Data {
        public:
            ~Data(){
                delete [] map;
                delete [] names;
            }

            bool loadFromFile(std::string path){
                unsigned int *size;
                char *file = hg::io::File(&path[0], size);
                if(size == 0){ delete [] file; delete size; return false; }

                unsigned int offset = 0;

                w = hg::bit::ptoui(file);
                offset += 4;

                h = hg::bit::ptoui(file + offset);
                offset += 4;

                map = new unsigned int[w * h];

                unsigned short base = hg::bit::ptous(file + offset);
                offset += 2;

                namesSize = hg::bit::ptoui(file + offset);
                names = new std::string[namesSize];
                offset += 4;

                unsigned int overflow = hg::bit::ptoui(file + offset);
                offset += 4;

                #ifdef GE_DEBUG
                    printf("w: %d, h: %d, b: %d, o: %u\n", w, h, (int)base, overflow);
                #endif

                for(unsigned int i = 0; i < namesSize; i++){
                    std::string temp = "";
                    for(; file[offset] != char(0); offset++){ temp += file[offset]; }
                    temp += file[offset];
                    offset++;

                    names[i] = temp;
                }

                #ifdef GE_DEBUG
                    printf("offset: %d\n", offset);
                #endif

                offset += (overflow == 0)? 0 : (sizeof(unsigned int) * hg::BYTE) - overflow; //todo: fix later

                unsigned short *currBit = new unsigned short(0x0);
                for(unsigned int i = 0; i < w * h; i++){
                    map[i] = getui(base, file, &offset, currBit);
                }

                for(unsigned int i = 0; i < w * h; i++){ printf("%s ", names[map[i]].c_str()); }

                delete currBit;
                delete size;
                delete [] file;

                return true;
            }

            std::string operator[](int index){ return names[map[index]]; }

            unsigned int width(){ return w; }
            unsigned int height(){ return h; }

        private:
            unsigned int getui(unsigned short &base, char *file, unsigned int *fileIndex, unsigned short *currBit){
                unsigned int ui = 0;
                for(unsigned short i = 1; i <= base; i++){
                    bool temp = (hg::bit::getValAt(file, fileIndex, currBit)? 1 : 0);
                    ui += (temp? 1 : 0) << (base - i);
                }

                return ui;
            }

            unsigned int w;
            unsigned int h;
            unsigned int *map;

            std::string *names;
            unsigned int namesSize;
        };
    }
}

#endif //GE_LEVEL_HPP