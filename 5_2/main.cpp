#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class HtmlBuilder;

class HTMLElement
{
private:
    string name, text;
    vector<HTMLElement> elements;

    const size_t indent_size = 2;

    HTMLElement(){}
    HTMLElement(string n, string t) : name(n), text(t)
    {}

public:
    friend HtmlBuilder;

    string str(int indent = 0) const
    {
      ostringstream oss;
      string i(indent_size*indent, ' ');
      oss << i << "<" << name << ">" << endl;
      if(text.size() > 0)
      {
          oss << string(indent_size*(indent + 1), ' ') << text << endl;
      }

      for(const auto & e : elements)
      {
          oss << e.str(indent + 1);
      }
      oss << i << "</" << name << ">" << endl;
      return oss.str();
    }
};

class HtmlBuilder
{
private:
    HTMLElement root;
public:
    HtmlBuilder(string root_name)
    {
        root.name = root_name;
    }

    HtmlBuilder & add_child(string child_name, string child_text)
    {
        HTMLElement e(child_name, child_text);
        root.elements.emplace_back(e);

        return *this;
    }

    string str() const
    {
        return root.str();
    }

    static HtmlBuilder build(string root_name)
    {
        return {root_name};
    }

    HTMLElement operator()()
    {
        return root;
    }

    operator HTMLElement()
    {
        return root;
    }

    HTMLElement build()
    {
        return root;
    }
};

int main()
{
    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello").add_child("li", "world");
    cout << builder.str() << endl;

    auto builder2 = HtmlBuilder::build("ui").add_child("li", "helloWorld").add_child("li","godbyeWorld");
    cout << builder2.str() << endl;

    HTMLElement e = builder2();
    cout << e.str();

    HTMLElement e2 = HtmlBuilder::build("ui").add_child("li", "helloWorld2").add_child("li","godbyeWorld2");
    cout << e2.str() << endl;

    HTMLElement e3 = HtmlBuilder::build("ui").add_child("li", "helloWorld3").add_child("li","godbyeWorld3").build();
    cout << e3.str() << endl;

    return 0;
}
