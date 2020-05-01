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

        HashTable<T, Functor>& operator=(const HashTable<T, Functor>& other) noexcept
        {
            hash = other.hash;
            length = other.length;
            table = other.table;
        }

        HashTable(const HashTable<T, Functor>& other)
        {
            hash = other.hash;
            length = other.length;
            table = new List<T>[length]();
            for(int i = 0; i < length; ++i)
            {
                table[i] = other.table[i];
            }
        }

        HashTable(HashTable<T, Functor>&& other) noexcept
        {
            swap(*this, other);
        }

        HashTable& operator=(HashTable<T, Functor>&& other) noexcept
        {
            swap(*this, other);
            return *this;
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

        bool contains(T value) noexcept
        {
            int hashed = hash(value);
            return table[hashed].contains(value);
        }

        void dump_lists_lens(std::ofstream& out) const
        {
            for(int i = 0; i < length; ++i)
            {
                out << table[i].size() << "\n";
            }
        }

        void clear()
        {
            for(int i = 0; i < TABLE_SIZE; ++i)
            {
                table[i].clear();
            }
        }

        friend void swap(HashTable<T, Functor>& first, HashTable<T, Functor>& second) noexcept
        {
            std::swap(first.length, second.length);
            std::swap(first.hash, second.hash);
            std::swap(first.table, second.table);
        }
};
