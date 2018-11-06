#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

enum class OutputFormat
{
    markdown,
    html
};

struct ListStrategy
{
    virtual void start(ostringstream & os) {}
    virtual void add_list_item(ostringstream & os, const string & item) = 0;
    virtual void end(ostringstream & os) {}
};

struct MarkdownListStrategy : ListStrategy
{
    void add_list_item(ostringstream &os, const string &item) override
    {
        os << "* " << item << endl;
    }
};


struct HtmlListStrategy : ListStrategy
{
    void start(ostringstream &os) override
    {
        os << "<ul>\n";
    }

    void add_list_item(ostringstream &os, const string &item) override
    {
        os << "   <li>" << item << "</li>\n";
    }

    void end(ostringstream &os) override
    {
        os << "</ul>\n";
    }
};

template <typename LS>
struct TextProcessor
{
    void clear()
    {
        oss.str("");
        oss.clear();
    }

    void append_list(const vector<string> & items)
    {
        list_strategy.start(oss);
        for(auto & item : items)
        {
            list_strategy.add_list_item(oss, item);
        }
        list_strategy.end(oss);
    }

    string str() const
    {
        return oss.str();
    }

private:
    ostringstream oss;
    LS list_strategy;
};

int main()
{
    vector<string> items {"foo", "bar", "baz"};

    TextProcessor<MarkdownListStrategy> tp1;
    tp1.append_list(items);
    cout << tp1.str() << endl;

    TextProcessor<HtmlListStrategy> tp2;
    tp2.append_list(items);
    cout << tp2.str() << endl;

    return 0;
}

