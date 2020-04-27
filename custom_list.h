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
            new_node->link(back_);
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
            while(cur && strcmp(cur->get_value(), value) != 0)
            {
                cur = cur->get_prev();
            }
            return cur ? true : false;
        }

        void pop_back()
        {
            if(size_)
            {
                Node<T>* old_back = back_;
                back_ = back_->get_prev();
                --size_;
                
                delete old_back;
            }
        }

        void erase(T value)
        {
            Node<T>* cur = back_;
            Node<T>* next = nullptr;
            while (cur && cur->get_value() != value)
            {
                next = cur;
                cur = cur->get_prev();
            }

            if(!cur)
            {
                return;
            }

            next->link(cur->get_prev());
            delete cur;
            --size;
        }

        void clear()
        {
            while(size_)
            {
                pop_back();
            }
        }

};