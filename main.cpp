#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>
#include <cstring>
#include <list>

#include "config.h"

template <typename T>
class Node
{
    private:
        T value;
        Node<T>* prev = nullptr;
    public:
        Node(T value) : value(value), prev(nullptr){}

        void link(Node<T>* other)
        {
            this->prev = other;
        }

        Node<T>* get_prev()
        {
            return prev;
        }
        
        T get_value()
        {
            return value;
        }
};

template <typename T>
class List
{
    private:
        int size_ = 0;
        Node<T>* back_ = nullptr;
    public:
        void push_back(T value)
        {
            if(!size_)
            {
                back_ = new Node<T>(value);
                ++size_;
                return;
            }

            Node<T>* new_node = new Node<T>(value);
            new_node->link(back_);
            ++size_;
        }

        int size()
        {
            return size_;
        }

        bool contains(T value)
        {
            Node<T>* cur = back_;
            while(cur && strcmp(cur->get_value(), value) != 0)
            {
                cur = cur->get_prev();
            }
            return cur ? true : false;
        }

        void erase(T value){}

};


class HashFunction
{
    public:
        HashFunction() = default;
        ~HashFunction() = default;

        virtual int operator()(char* string)
        {
            return 0;
        }
};

class ConstantHash : public HashFunction
{
    public:
        ConstantHash() = default;
        ~ConstantHash() = default;
        int operator()(char* string)
        {
            return 0;
        }
};

class StrlenHash : public HashFunction
{
    public:
        StrlenHash() = default;
        ~StrlenHash() = default;
        int operator()(char* string)
        {
            return strlen(string);
        }
};

class ASCIILenHash : public HashFunction
{
    public:
        ASCIILenHash() = default;
        ~ASCIILenHash() = default;
        int operator()(char* string)
        {
            int sum = 0;
            int len = strlen(string);
            while(*string)
            {
                sum += *string;
                ++string;
            }
            return sum / len;
        }
};

class ASCIIXorRotate : public HashFunction
{
    public:
        ASCIIXorRotate() = default;
        ~ASCIIXorRotate() = default;
        int operator()(char* string)
        {
            if(!*string)
            {
                return 0; 
            }

            uint32_t hash = 0;
            while(*string)
            {
                hash = hash ^ (*string);
                uint32_t oldest_bit = hash & 0x80000000;
                oldest_bit >>= 31;    
                hash <<= 1;
                hash |= oldest_bit;
                ++string;
            }
            return hash % TableSize;
        }
};

class JenkinsHash : public HashFunction
{
    public:
        JenkinsHash() = default;
        ~JenkinsHash() = default;
        int operator()(char* string)
        {
            int len = strlen(string);
            size_t i = 0;
            uint32_t hash = 0;

            while (i != len) 
            {
                hash += string[i++];
                hash += hash << 10;
                hash ^= hash >> 6;
            }
            hash += hash << 3;
            hash ^= hash >> 11;
            hash += hash << 15;
            return hash % TableSize;
        }
};

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