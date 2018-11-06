#include <iostream>
#include <string>
#include <algorithm>
#include <boost/iterator/iterator_facade.hpp>
using namespace std;

struct Node
{
    string value;
    Node * next {nullptr};

    Node(const string & value_)
        : value(value_)
    {}

    Node(const string & value_, Node * parrent)
        : value(value_)
    {
        parrent->next = this;
    }
};

struct ListIterator : boost::iterator_facade<ListIterator, Node, boost::forward_traversal_tag>
{
    Node * current{nullptr};

    ListIterator(){}

    ListIterator(Node * current_)
        : current(current_)
    {
    }

private:
    friend class boost::iterator_core_access;

    void increment()
    {
        current = current->next;
    }

    bool equal(const ListIterator & other) const
    {
        return other.current == current;
    }

    Node & dereference() const
    {
        return *current;
    }
};

int main()
{
    Node alfa{"alpha"};
    Node beta{"beta", &alfa};
    Node gama{"gama", &beta};

    for_each(ListIterator{&alfa}, ListIterator{}, [](const Node & n){ cout << n.value << endl;});

    return 0;
}

