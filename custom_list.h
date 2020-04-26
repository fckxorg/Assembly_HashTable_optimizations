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