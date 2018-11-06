#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Tag
{
    string name, text;
    vector<Tag> children;
    vector<pair<string, string>> attributes;

    friend std::ostream & operator<<(ostream &os, const Tag & tag)
    {
        os << "<" << tag.name;

        for(const auto & att : tag.attributes)
        {
            os << " " << att.first << "=\"" << att.second << "\"";
        }

        if(tag.children.size() == 0 && tag.text.length() == 0)
        {
            os << "/>" << endl;
        }
        else
        {
            os << ">" << endl;

            if(tag.text.length())
            {
                os << tag.text << endl;
            }

            for(const auto & child : tag.children)
            {
                os << child;
            }

            os << "</" << tag.name << ">" << endl;
        }

        return os;
    }

    Tag(const string & n, const string & t)
        : name(n), text(t)
    {}
    Tag(const string & n, const vector<Tag> & ch)
        : name(n), children(ch)
    {}
};

struct P : Tag
{
    P(string t)
        : Tag("p", t)
    {}

    P(initializer_list<Tag> children)
        : Tag{"p", children}
    {}
};

struct IMG : Tag
{
    explicit IMG(const string & url)
        : Tag("img", "")
    {
        attributes.emplace_back(make_pair("src", url));
    }
};

int main()
{
    cout <<
            P{
                IMG{"http://pokenon.com/pikatchu.png"}
            }
         << endl;

    return 0;
}

