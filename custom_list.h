#include <fstream>

template <typename T>
class Node
{
    Node<T>* next;
    Node<T>* prev;
    T value;

    public:
        Node(T value) : next(nullptr), prev(nullptr), value(value){};
        ~Node() = default;
        void link(Node<T>* other)
        {
            other->next = this;
            this->prev = other;
        }

        Node* getNext()
        {
            return next; 
        }

        Node* getPrev()
        {
            return prev;
        }

        T getValue()
        {
            return value;
        }
};

template <typename T>
class List
{
    private:
        Node<T>* front = nullptr;
        Node<T>* back = nullptr;
        int size = 0;
    public:
        List() = default;
        ~List()
        {
            Node<T>* cur = front;
            while(cur)
            {
                Node<T>* to_delete = cur;
                cur = cur->getNext();
                delete to_delete;
            }
        }

        void pushBack(T value)
        {
            if(!back)
            {
                back = new Node<T>(value);
                front = back;
                ++size;
                return;
            }

            auto new_node = new Node<T>(value);
            new_node->link(back);
            back = new_node;
            ++size;
        }

        void pushFront(T value)
        {
            if(!front)
            {
                pushBack(value);
                return;
            }
            auto new_node = new Node<T>(value);
            front->link(new_node);
            front = new_node;
            ++size;
        }

        bool contains(T value)
        {
            if(!size)
            {
                return false;
            }

            Node<T>* cur = front;
            while(cur)
            {
                if(cur->getValue() == value)
                {
                    return true;
                }
                cur = cur->getNext();
            }
            return false;
        }

        int find(T value)
        {
            if(!size)
            {
                return -1;
            }

            Node<T>* cur = front;
            int idx = 0;
            while(cur)
            {
                if(cur->getValue() == value)
                {
                    return idx;
                }
                cur = cur->getNext();
                ++idx;
            }
            return -1;
        }

        void pop_front()
        {
            front = front->getNext();
            delete front->getPrev();
            front->getPrev() = nullptr;
            --size;
        }

        void pop_back()
        {
            back = back->getPrev();
            delete back->getNext();
            back->getNext() = nullptr;
            --size;
        }

        void erase(T value)
        {
            if(front->getValue() == value)
            {
                pop_front();
            }

            Node<T>* cur = front;
            int idx = 0;
            while(cur->getNext())
            {
                if(cur->getValue() == value)
                {
                    --size;
                    cur->getNext()->link(cur->getPrev);
                    delete cur;
                    return;
                }
                cur = cur->getNext();
                ++idx;
            }

            if(back->getValue() == value)
            {
                pop_back();
            }
        }

        int length()
        {
            return size;
        }

        void clear()
        {
            while(size)
            {
                pop_back();
            }
        }

        void print(std::ofstream& out)
        {
            Node<T>* cur = front;
            while(cur)
            {
                out << cur->getValue() << " ";
                cur = cur->getNext();
            }
        }
};


