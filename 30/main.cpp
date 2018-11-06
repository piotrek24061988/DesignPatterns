#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

class FormattedText
{
    string plain_text;
    unique_ptr<bool[]> caps;
public:
    FormattedText(const string & s)
        : plain_text{s}, caps{new bool[plain_text.size()]}
    {
    }

    void capitalize(int start, int end)
    {
        for(auto i = start; i <= end; i++)
        {
            caps[i] = true;
        }
    }

    friend ostream & operator<<(ostream & os, const FormattedText & ft)
    {
        for(int i = 0; i < ft.plain_text.length(); i++)
        {
            os << char(ft.caps[i] ? toupper(ft.plain_text[i]) : ft.plain_text[i]);
        }
        return os;
    }
};

class BetterFormattedText
{
public:
    struct TextRange
    {
        int start, end;
        bool capitalize;

        bool covers(int position) const
        {
            return position >= start && position <= end;
        }
    };

    TextRange & get_range(int start, int end)
    {
        formatting.emplace_back(TextRange{start, end});
        return *formatting.rbegin();
    }

    BetterFormattedText(const string & s)
        : plain_text{s}
    {}

    friend ostream & operator<<(ostream & os, const BetterFormattedText & bft)
    {
        string s;
        for(int i = 0; i < bft.plain_text.length(); i++)
        {
            auto c = bft.plain_text[i];
            for(const auto & rng : bft.formatting)
            {
                if(rng.covers(i) && rng.capitalize)
                {
                    c = toupper(c);
                }
                s += c;
            }
        }
        return os << s;
    }

private:
    string plain_text;
    vector<TextRange> formatting;
};

int main()
{
    FormattedText text{"This is my beautiful country"};
    text.capitalize(10, 20);
    cout << text << endl << endl;


    BetterFormattedText text2{"This is my beautiful country"};
    text2.get_range(10, 20).capitalize = true;
    cout << text2 << endl;
    return 0;
}

