

#ifndef UNTITLED_HASHFUNCTION_H
#define UNTITLED_HASHFUNCTION_H

#include <vector>
#include <list>
#include <iostream>
class String_Hash_function{
public:
    inline size_t operator()(const std::string& str){  //Алгоритъм на Робър Седжуик взет от този сайт : http://www.partow.net/programming/hashfunctions/index.html#RSHashFunction
        unsigned int b    = 378551;
        unsigned int a    = 63689;
        size_t hash = 0;
        unsigned int i    = 0;

        for (i = 0; i < str.length(); ++i)
        {
            hash = hash * a + str[i];
            a    = a * b;
        }

        return hash;
    }
};



template<class K, class T, class HashFunc>
class Hash {
    typedef std::pair<K,T> Pair;
    typedef std::list<Pair>
    Bucket;
    typedef std::vector<Bucket> Table;
    Table table;
    HashFunc hf;
    int size;
    static constexpr double Max_LoadFactor=0.75;
    static const size_t InitialSize = 100;

    double getloadfactor(){
        return size>0 ? size/table.size():0;
    }

    void resize();

    size_t gethash(const K &key) {
        return hf(key) % table.size();
    }

public:
    Hash();

    bool insert(const K &key, const T &data);

     std::pair<const K,T>* operator[](const K &);
     bool erase(const K&);
     const T& getdata()const;//Връща "първия" елемент.
     int getsize() const{
         return size;
     }


};

template<class K, class T, class HashFunc>
Hash<K, T, HashFunc>::Hash():size(0) {
    table.resize(InitialSize);
}

template<class K, class T, class HashFunc>
bool Hash<K, T, HashFunc>::insert(const K &key, const T &data) {
    Pair newel{key, data};
    size_t idx = gethash(key);
    typename Bucket::iterator it = table[idx].begin();
    while (it != table[idx].end()) {
        if (it->first == key) {
            std::cout << "Element already exists!" << std::endl;
            return false;
        }
        it++;
    }
        if (getloadfactor() > Max_LoadFactor) {
            resize();
            idx = gethash(key);

        }
        table[idx].push_front(newel);
        ++size;
        return true;

}

template<class K, class T, class HashFunc>
void Hash<K, T, HashFunc>::resize() {
    Table temp;
    temp.resize(table.size() * 2);
    std::swap(temp, table);
    size_t idx;
    for (const Bucket &bucket : temp) {
        for (const Pair &el : bucket) {
            idx = gethash(el.first);
            table[idx].push_front(el);
        }
    }

}

template<class K, class T, class HashFunc>
 std::pair<const K,T>* Hash<K, T, HashFunc>::operator[](const K & key) {
    size_t idx=gethash(key);
    typename Bucket::iterator it=table[idx].begin();
    while(it!=table[idx].end()){
        if (it->first==key)
            return reinterpret_cast<std::pair<const K,T>*>(&*it);
        ++it;
    }
    return  nullptr;


}

template<class K, class T, class HashFunc>
bool Hash<K, T, HashFunc>::erase(const K & key) {
    size_t idx=gethash(key);
    typename Bucket::iterator it=table[idx].begin();
    while(it!=table[idx].end()){
        if(it->first==key){
            table[idx].erase(it);
            --size;
            return true;
        }
        it++;
    }
    return  false;
}

template<class K, class T, class HashFunc>
const T &Hash<K, T, HashFunc>::getdata() const {
    for (const Bucket& bucket:table){
        if(bucket.size()!=0){
            return bucket.front().second;
        }
    }
}


#endif //UNTITLED_HASHFUNCTION_H
