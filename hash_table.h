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
