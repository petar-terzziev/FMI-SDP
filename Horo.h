

#include "../Hash_Map.h"
#include <string>
#include <fstream>
#ifndef UNTITLED_HORO_H
#define UNTITLED_HORO_H

class Horo {

    struct Grip {
        std::string name;
        Grip* left;
        Grip* right;
        bool isholdingleft;
        bool isholdingright;
        Grip(const std::string& );
    };
    Hash<std::string,Grip*,String_Hash_function> horo;
    void free();
    void copy(const Horo&);
public:
    Horo (const std::string&);
    Horo (const Horo&);
    Horo& operator=(const Horo&);
    ~Horo();
    void proccess_command(const std::string&);
    void add(const std::string&,const std::string&,const std::string&);
    void remove(const std::string&);
    void info(const std::string&);
    void swap(const std::string&,const std::string& );

    void print();
};



#endif //UNTITLED_HORO_H
