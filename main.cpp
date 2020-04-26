#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>
#include <list>

#include "hashes.h"
#include "custom_list.h"



template <typename T, typename Functor>
class HashTable
{
    private:
        List<T>* table = nullptr;
        int length = 0;
        Functor hash;
    public:
        HashTable(int size, Functor hash_functor) : length(size), hash(hash_functor) 
        {
            table = new List<T>[size]();    
        }

        ~HashTable()
        {
            delete[] table;
        }

        HashTable& operator=(const HashTable& other)
        {
            hash = other.hash;
            length = other.length;
            table = other.table;
        }

        HashTable(const HashTable& other)
        {
            hash = other.hash;
            length = other.length;
            table = new List<T>[length]();
            for(int i = 0; i < length; ++i)
            {
                table[i] = other.table[i];
            }
        }
       
        void add(T value)
        {
            int hashed = hash(value);
            table[hashed].push_back(value);
        }

        void remove(T value)
        {
            int hashed = hash(value);
            table[hashed].erase(value);
        }

        bool contains(T value)
        {
            int hashed = hash(value);
            return table[hashed].contains(value);
        }

        void dump_lists_lens(std::ofstream& out)
        {
            for(int i = 0; i < length; ++i)
            {
                out << table[i].size() << "\n";
            }
        }
};


#define HASH JenkinsHash

int main()
{
    std::ifstream in;
    in.open("test_data/word_set.txt");
    char** words = new char*[N_WORDS]();
    for(int i = 0; i < N_WORDS; ++i)
    {
        words[i] = new char[100]();    
    }

    auto table = HashTable<char*, HASH>(TableSize, HASH());


    for(int i = 0; i < N_WORDS; ++i)
    {
        in >> words[i];
        table.add(words[i]);
    }

    for(int i = 0; i < N_SAMPLES; ++i)
    {
        int word_idx = rand() % N_WORDS;
        table.contains(words[word_idx]);
    }

    std::ofstream out;
    out.open("test.out");
    out << "ttt";
    table.dump_lists_lens(out);
    out.close();
    in.close();

    for(int i = 0; i < N_WORDS; ++i)
    {
        delete[] words[i];
    }

    delete[] words;
    return 0;
}