#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <fstream>
#include <iostream>
#include <map>

namespace ge {
    namespace resource {
        template <class ResourceObj>
        class ResourceObjArr {
        public:
            ResourceObjArr(ResourceObj *objs, unsigned int size = 1): objs(objs), size(size){}
            ~ResourceObjArr(){ delete [] objs; }
            
            ResourceObj &operator[](int index){ return objs[index]; }
            unsigned int getSize(){ return size; }

        protected:
            ResourceObj *objs;
            unsigned int size;
        };

        template <class ResourceObj>
        class Resource {
        public:
            Resource(){}
            ~Resource(){ 
                for(const std::pair<std::string, ResourceObjArr<ResourceObj>*> &i : objs){ delete i.second; }
                objs.clear();
            }

            virtual void read(std::string filepath){
                std::filebuf fb;
                if (fb.open(filepath, std::ios::in)) {
                    std::istream is(&fb);
                    while(is){
                        std::string temp;
                        std::getline(is, temp);
                        if(temp.find(':') == std::string::npos){ continue; }

                        std::string root = filepath.substr(0, filepath.find_last_of("/") + 1);
                        load(root + temp.substr(temp.find(':') + 2, temp.size() - 1), temp.substr(0, temp.find(':')));
                    }

                    fb.close();
                }
            }

            virtual void load(std::string filepath, std::string name){
                ResourceObj *obj = new ResourceObj[1];

                if(!obj->loadFromFile(filepath)){
                    delete obj;
                    std::cout << "Error: filepath '" << filepath << "' failed to load" << std::endl;
                    std::exit(-1);
                }
                objs[name] = new ResourceObjArr<ResourceObj>(obj);
            }

            virtual void unload(std::string filepath){
                std::filebuf fb;
                if (fb.open(filepath, std::ios::in)) {
                    std::istream is(&fb);
                    while(is){
                        std::string temp;
                        std::getline(is, temp);
                        if(temp.find(':') == std::string::npos){ continue; }

                        temp = temp.substr(0, temp.find(':'));
                        delete objs[temp];
                        objs.erase(temp);
                    }

                    fb.close();
                }
            }

            ResourceObjArr<ResourceObj> &getResource(std::string name){ return *objs[name]; }
            std::map<std::string, ResourceObjArr<ResourceObj>> &getResources(){ return objs; }

        protected:
            std::map<std::string, ResourceObjArr<ResourceObj>*> objs;
        };
    }
}

#endif // !RESOURCE_HPP