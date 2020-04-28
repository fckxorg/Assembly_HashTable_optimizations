#include <cstdint>
#include <cstring>
#include "config.h"


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
            return hash % TABLE_SIZE;
        }
};

class JenkinsHash : public HashFunction
{
    public:
        JenkinsHash() = default;
        ~JenkinsHash() = default;
        int operator()(char* string)
        {
            uint32_t i = 0;
            uint32_t len = strlen(string);
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
            return hash % TABLE_SIZE;
        }
};


