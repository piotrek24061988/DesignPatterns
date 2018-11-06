#include <iostream>
using namespace std;

template<typename T>
struct BinaryTree;

template <typename T>
struct Node
{
    T value = T();

    Node<T> * left_child{nullptr}, * right_child{nullptr}, * parrent{nullptr};
    BinaryTree<T> * tree{nullptr};

    Node(T value_) : value{value_}
    {}

    Node(T value_, Node<T> * left_, Node<T> * right_)
        : value{value_}, left_child{left_}, right_child{right_}
    {
        left_child->tree = right_child->tree = tree;
        left_child->parrent = right_child->parrent = this;
    }

    void set_tree(BinaryTree<T> * t)
    {
        tree = t;
        if(left_child)
        {
            left_child->set_tree(t);
        }
        if(right_child)
        {
            right_child->set_tree(t);
        }
    }

    ~Node()
    {
        if(left_child)
        {
            delete left_child;
        }
        if(right_child)
        {
            delete right_child;
        }
    }
};

template <typename T>
struct BinaryTree
{
    Node<T> * root{nullptr};

    BinaryTree(Node<T> * root_)
        : root{root_}
    {
       root->set_tree(this);
    }

    ~BinaryTree()
    {
        if(root)
        {
            delete root;
        }
    }

    template<typename U>
    struct PreOrderIterator
    {
        Node<U> * current;

        PreOrderIterator(Node<U> * current_)
            : current(current_)
        {}

        bool operator!=(const PreOrderIterator<U> & other)
        {
            return current != other.current;
        }

        PreOrderIterator<U> & operator++()
        {
            if(current->right_child)
            {
                current = current->right_child;
                while(current->left_child)
                {
                    current = current->left_child;
                }
            }
            else
            {
                Node<T> * p = current->parrent;
                while(p && current == p->right_child)
                {
                    current = p;
                    p = p->parrent;
                }
                current = p;
            }
            return *this;
        }

        Node<U> & operator*()
        {
            return *current;
        }
    };

    using iterator = PreOrderIterator<T>;

    iterator begin()
    {
        Node<T> * n = root;

        if(n)
        {
            while(n->left_child)
            {
                n = n->left_child;
            }
        }
        return iterator{n};
    }

    iterator end()
    {
        return iterator{nullptr};
    }
};

int main()
{

    //     me
    //    /  \
    // mother father
    //  /  \
    //m.m  m.f

    BinaryTree<string> family
    {
        new Node<string>
        { "me",
           new Node<string>
            { "mother",
                new Node<string> {"mothers mother"},
                new Node<string> {"mothers father"}
            },
           new Node<string> {"father"}
        }
    };

    for(auto it = family.begin(); it!=family.end(); ++it)
    {
        cout << (*it).value << "\n";
    }

    return 0;
}

