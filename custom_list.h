inline bool fastcmpeq(char* str1, char* str2)
{
    unsigned long long* chunk_arr1 = reinterpret_cast<unsigned long long*>(str1);
    unsigned long long* chunk_arr2 = reinterpret_cast<unsigned long long*>(str2);
    unsigned long long int result = 0;
        asm("mov    rdi, %1\n\t"       
            "mov    rsi, %2\n\t"
            "mov    ecx, 6\n\t"
            "cmp_loop:\n\t"
            "cmp    ecx, 0\n\t"
            "je     cmp_loop_end\n\t"
            "dec    ecx\n\t"
            "mov    rax, [rdi]\n\t"
            "mov    rbx, [rsi]\n\t"
            "xor    rax, rbx\n\t"
            "cmp    rax, 0\n\t"
            "add    rsi, 8\n\t"
            "add    rdi, 8\n\t"
            "je     cmp_loop\n\t"
            "cmp_loop_end:\n\t"
            "mov    %0, rax\n\t"
            :"=r"(result)             
            :"r"(chunk_arr1), "r"(chunk_arr2)    
            : "rax", "rbx", "rcx", "rdi", "rsi"        
            );

    return !result;
}


template <typename T>
class Node
{
    public:
        Node<T>* prev = nullptr;
        T value;
        Node(T value) : value(value), prev(nullptr){}
        ~Node() = default;
};

template <typename T>
class List
{
    private:
        int size_ = 0;
        Node<T>* back_ = nullptr;
    public:
        List() = default;
        ~List() 
        {
            clear();
        }

        void push_back(T value)
        {
            if(!size_)
            {
                back_ = new Node<T>(value);
                ++size_;
                return;
            }

            Node<T>* new_node = new Node<T>(value);
            new_node->prev = back_;
            back_ = new_node;
            ++size_;
        }

        int size() const noexcept
        {
            return size_;
        }

        bool contains(T value) const noexcept
        {
            Node<T>* cur = back_;
            while(cur && fastcmpeq(cur->value, value) != 0)
            {
                cur = cur->prev;
            }
            return cur ? true : false;
        }

        void pop_back()
        {
            if(size_)
            {
                Node<T>* old_back = back_;
                back_ = back_->prev;
                --size_;
                
                delete old_back;
            }
        }

        void erase(T value)
        {
            Node<T>* cur = back_;
            Node<T>* next = nullptr;
            while (cur && cur->value != value)
            {
                next = cur;
                cur = cur->prev;
            }

            if(!cur)
            {
                return;
            }

            next->prev = cur->prev;
            delete cur;
            --size_;
        }

        void clear()
        {
            while(size_)
            {
                pop_back();
            }
        }

};
