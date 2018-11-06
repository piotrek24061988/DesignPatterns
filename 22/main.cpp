#include <iostream>
#include <vector>
using namespace std;

template <typename Self>
struct SomeNeurons
{
    template <typename T>
    void connectTo(T & other)
    {
        for(auto & from : *static_cast<Self*>(this))
        {
            for(auto & to : other)
            {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }
};

struct Neuron : SomeNeurons<Neuron>
{
    vector<Neuron*> in, out;
    unsigned int id;

    Neuron()
    {
        static int id_{1};
        id = id_++;
    }

    void connect_to(Neuron & other)
    {
        out.push_back(&other);
        other.in.push_back(this);
    }

    friend ostream & operator<<(ostream & os, const Neuron & neuron)
    {
        for(auto p : neuron.in)
        {
            os << p->id << "-->[" << neuron.id << "]" << endl;
        }
        for(auto p : neuron.out)
        {
            os << "[" << neuron.id << "]-->" << p->id << endl;
        }
        return os;
    }

    Neuron * begin()
    {
        return this;
    }

    Neuron * end()
    {
        return this + 1;
    }
};

struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer>
{
    NeuronLayer(int count)
    {
        while(count-- > 0)
        {
            emplace_back(Neuron{});
        }
    }

    friend ostream & operator<<(ostream & os, const NeuronLayer & nl)
    {
        for(auto & n : nl)
        {
            os << n;
        }
        return os;
    }
};

int main()
{
    Neuron n1, n2;
    n1.connect_to(n2);
    cout << n1 << n2 << endl;

    NeuronLayer nl1{2}, nl2{3};
    n1.connectTo(nl1);
    nl2.connectTo(n2);
    nl1.connectTo(nl2);


    cout << endl << endl << nl1 << endl;

    return 0;
}

