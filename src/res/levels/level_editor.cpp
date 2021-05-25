#include <hg/lib.hpp>
#include <stdio.h>

namespace level_editor {
    //            fileData          fileSize      pixelDataOffset             width            height         bitsPerPixel
    bool checkBMP(char *&f, unsigned int *&s, unsigned int *&pxdo, unsigned int *&w, unsigned int *&h, unsigned char *&bpx){
        if(*s < 26 || f[0] != 0x42 || f[1] != 0x4d || hg::bit::ptoui(f + 2) != *s){ //make sure the head has correct values
            #ifdef DEBUG
                printf("%u < 26 || %d != 0x42 || %d != 0x4d || %x != %x\n", *s, f[0], f[1], hg::bit::ptoui(f + 2), *s);
            #endif

            return false;
        }

        //get all needed values from bmp
        pxdo = new unsigned int( hg::bit::ptoui(f + 10));
        w =    new unsigned int( hg::bit::ptoui(f + 18));
        h =    new unsigned int( hg::bit::ptoui(f + 22));
        bpx =  new unsigned char(hg::bit::ptoui(f + 28) / hg::BYTE);

        #ifdef DEBUG
            printf("size: %u\n", *s);
            printf("pxOffset: %u\n", *pxdo);
            printf("width: %u\n", *w);
            printf("height: %u\n", *h);
            printf("bits per px: %u\n", *bpx);
        #endif

        return true;
    }

    void setHeaders(char *&of, unsigned int *&w, unsigned int *&h, unsigned short *&b, unsigned int *&kvs, unsigned int *o){
        of[0] = char(0xff & *w); // file size
        of[1] = char((0xff00 & *w) >> 8);
        of[2] = char((0xff0000 & *w) >> 16);
        of[3] = char((0xff000000 & *w) >> 24);

        of[4] = char(0xff & *h); // file size
        of[5] = char((0xff00 & *h) >> 8);
        of[6] = char((0xff0000 & *h) >> 16);
        of[7] = char((0xff000000 & *h) >> 24);

        of[8] = char(0xff & *b); // base size
        of[9] = char((0xff00 & *b) >> 8);

        of[10] = char(0xff & *kvs); // num of titles
        of[11] = char((0xff00 & *kvs) >> 8);
        of[12] = char((0xff0000 & *kvs) >> 16);
        of[13] = char((0xff000000 & *kvs) >> 24);

        of[14] = char(0xff & *o); // overflow
        of[15] = char((0xff00 & *o) >> 8);
        of[16] = char((0xff0000 & *o) >> 16);
        of[17] = char((0xff000000 & *o) >> 24);
    }

    bool appendtoui(unsigned char *f, unsigned short *fi, unsigned int *v, unsigned int *o, unsigned short *b){
        for(unsigned int i = *fi; 0 < *b - *o; ++*fi){
            if(*v >= (unsigned int)(1 << *b)){ printf("error: value '%u' is greater than '%u'", *v, 1 << *b); std::exit(-1); }
            *f += (*v & (1 << *o)) << i;

            ++*o;
            if(*fi == (sizeof(unsigned char) * hg::BYTE) - 1){ *fi = 0; return true; }
        }

        return false;
    }

    bool stripKey(char *&file, unsigned int *&size, unsigned int *&keyValue, unsigned int *&keyValueSize, unsigned int *&outputValue, unsigned int *&outputValueSize){
        hg::Stack<unsigned int> *stack = new hg::Stack<unsigned int>();
        hg::Stack<hg::Pair<unsigned int, unsigned int>> *startAndSize = new hg::Stack<hg::Pair<unsigned int, unsigned int>>(); // pair<starting index of var, length of var>

        if(6 < *size){ stack->push(0); }

        unsigned int *p = new unsigned int(7);
        bool *crlf = new bool(hg::bit::isCRLF(file + 7));
        bool *foundVar = new bool(file[*crlf? 8 : 7] != '\n');

        for(unsigned int i = 1; i < *size; i++){
            if(file[i] == '\n' && i + 6 < *size){
                stack->push(i + 1);

                if(*foundVar){ startAndSize->push(hg::Pair<unsigned int, unsigned int>(*p, (i - 1) - *p)); }
                *p = i + 8;
                *foundVar = file[*crlf? 8 : 7] != '\n';
            }
        }

        if(*foundVar){ startAndSize->push(hg::Pair<unsigned int, unsigned int>(*p, (*size - *p) - 1)); }
        delete crlf;
        delete foundVar;
        delete p;

        if(stack->getSize() == 0){ delete stack; return false; }
        outputValueSize = new unsigned int(startAndSize->getSize() * 2);
        outputValue = new unsigned int[*outputValueSize];
        for(unsigned int i = *outputValueSize; i > 0; i-=2){
            hg::Pair<unsigned int, unsigned int> temp = startAndSize->pop();
            outputValue[i - 1] = temp.first;
            outputValue[i - 2] = temp.second;
        }
        delete startAndSize;

        keyValueSize = new unsigned int(stack->getSize());
        keyValue = new unsigned int[*keyValueSize];
        for(unsigned int i = *keyValueSize; i > 0; i--){ keyValue[i - 1] = stack->pop(); }
        delete stack;

        return true;
    }

    bool convert(char *&fd, unsigned int *&fs, char *&kd, unsigned int *&ks, char *&of, unsigned int *&ofs, unsigned int *&ov, unsigned int *&ovs, unsigned int *&pxdo, unsigned int *&w, unsigned int *&h, unsigned char *&bpx, unsigned int *&kv, unsigned int *&kvs){
        if(!checkBMP(fd, fs, pxdo, w, h, bpx)){  printf("Error: please make sure to use a valid bmp file\n");  return false; }
        if(!stripKey(kd, ks, kv, kvs, ov, ovs)){ printf("Error: please make sure to use a valid vars file\n"); return false; }

        hg::Stack<unsigned char *> *fstack = new hg::Stack<unsigned char *>(); // final stack

        unsigned char *f = new unsigned char(0);
        unsigned short *b = hg::bit::getClosestBit(kvs);
        unsigned short *fi = new unsigned short(0);
        unsigned int *o = new unsigned int(0);

        for(unsigned int y = 0; y < *h; y++){
            for(unsigned int x = *w - 1; x + 1 > 0; x--){
                for(unsigned int j = 0; j < *kvs; j++){
                    if((((y * *w) + x) * *bpx) + *pxdo >= *fs){ break; }
                    if(hg::bit::ptopx(fd + (((y * *w) + x) * *bpx) + *pxdo) == hg::bit::cstorgbhex(kd + kv[j])){
                        while(*o < *b){ if(appendtoui(f, fi, &j, o, b)){ fstack->push(f); f = new unsigned char(0); }; }
                        *o = 0;
                        break;
                    }
                }
            }
        }

        if(*o != 0){ fstack->push(f); }
        printf("overflow: %u\n", *o);

        delete fi;

        unsigned int *fo = new unsigned int(18); //this is for headers
        unsigned int *ofi = new unsigned int(18);
        for(unsigned int i = 0; i < *ovs; i+=2){ *fo += ov[i] + 1 + 1; }

        ofs = new unsigned int(fstack->getSize() + *fo);
        of = new char[*ofs];

        setHeaders(of, w, h, b, kvs, o);
        delete o;

        #ifdef DEBUG
            printf("ovs: %u", *ovs);
        #endif

        for(unsigned int i = 0; i < *ovs; i+=2){
            for(unsigned int j = 0; j <= ov[i]; j++){
                of[*ofi] = kd[ov[i + 1] + j];
                ++*ofi;
            }
            of[*ofi] = char(0);
            ++*ofi;
        }

        printf("ofi: %u\n", *ofi);

        for(; *ofi < *ofs; ++*ofi){
            if(fstack->getSize() == 0){ break; }
            f = fstack->pop();
            of[*ofi] = *f;
            delete f; 
        }
        delete fstack;

        delete b;
        delete fo;
        delete ofi;

        return true;
    }

    bool BMPToBinary(int &argc, char **&argv){
        unsigned int *fSize, *pixelDataOffset, *width, *height;
        unsigned char *bytesPerPixel;
        char *fData = hg::io::File(argv[1], fSize);

        unsigned int *kSize;
        char *kData = hg::io::File(argv[2], kSize);

        unsigned int *keyValues, *keyValueSize;

        unsigned int *oSize, *oVars, *oVarsSize;
        char *oData;

        if(convert(fData, fSize, kData, kSize, oData, oSize, oVars, oVarsSize, pixelDataOffset, width, height, bytesPerPixel, keyValues, keyValueSize)){
            hg::io::Write(argv[3], oData, oSize);
        }

        delete fSize;
        delete pixelDataOffset;
        delete width;
        delete height;
        delete bytesPerPixel;
        delete [] fData;

        delete kSize;
        delete [] kData;

        delete [] keyValues;
        delete keyValueSize;

        delete oSize;
        delete [] oVars;
        delete oVarsSize;
        delete [] oData;

        return true;
    }
}

int main(int argc, char **argv){
    if(argc < 4){ printf("too few arguments: le.exe your.bmp your.vars output.level_data"); return -1; }
    if(argc > 4){ printf("too many arguments: le.exe your.bmp your.vars output.level_data"); return -1; }

    level_editor::BMPToBinary(argc, argv);

    return 0;
}