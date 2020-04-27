#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>
#include <list>

#include "hashes.h"
#include "custom_list.h"
#include "hash_table.h"


#define HASH JenkinsHash

int main()
{
    std::ifstream in;
    in.open("test_data/word_set.txt");
    char** words = new char*[N_WORDS]();
    for(int i = 0; i < N_WORDS; ++i)
    {
        words[i] = new char[WORD_SIZE]();    
    }

    auto table = HashTable<char*, HASH>(TABLE_SIZE, HASH());


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