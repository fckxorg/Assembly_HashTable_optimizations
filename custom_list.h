template <typename T>
class Node
{
    public:
        Node<T>* prev = nullptr;
        T value;
        Node(T value) : value(value), prev(nullptr){}
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

        int size()
        {
            return size_;
        }

        bool contains(T value)
        {
            Node<T>* cur = back_;
            while(cur && strcmp(cur->value, value) != 0)
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
