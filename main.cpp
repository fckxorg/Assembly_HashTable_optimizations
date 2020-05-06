#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>

#include "hashes.h"
#include "hash_table.h"

typedef JenkinsHash HASH;

int main()
{
    std::ifstream in;
    in.open(WORD_SET);

    auto table = HashTable<char*, HASH>(TABLE_SIZE, HASH());
    char* words = new char[N_WORDS * WORD_SIZE]();
    
    for(int i = 0; i < N_WORDS * WORD_SIZE; i += WORD_SIZE)
    {
        in >> (words + i);
        table.add(words + i);
    }

    for(int i = 0; i < N_SAMPLES; ++i)
    {
        int word_idx = rand() % N_WORDS;
        table.contains(words + word_idx * 48);
    }

    std::ofstream out;
    out.open(LOG_PATH);
    table.dump_lists_lens(out);

    out.close();
    in.close();

    delete[] words;
    return 0;
}
