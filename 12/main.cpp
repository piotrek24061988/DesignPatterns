#include <iostream>
#include <memory>
#include <map>
#include <functional>
using namespace std;

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
using namespace boost;


struct Address
{
    string street, city;
    int suite;

    Address(const string & s, const string & c, int su)
        : street(s), city(c), suite(su)
    {
    }

    Address() = default;

    Address(const Address & ad)
        : street(ad.street), city(ad.city), suite(ad.suite)
    {
    }

    friend ostream & operator<<(ostream & os, const Address & ad)
    {
        os << "street: " << ad.street << " city: " << ad.city << " suite: " << ad.suite;
        return os;
    }

private:
    friend class serialization::access;

    template<typename archive>
    void serialize(archive & ar, const unsigned int ver)
    {
        ar & street;
        ar & city;
        ar & suite;
    }
};

struct Contact
{
    string name;
    Address * address;

    Contact(const string & n, Address * a)
        : name(n), address(a)
    {
    }

    Contact() = default;

    Contact(const Contact & c)
        : name(c.name),
          address(new Address(*(c.address)))
    {
    }

    ~Contact()
    {
        if(address)
        {
            delete address;
            address = nullptr;
        }
    }

    friend ostream & operator<<(ostream & os, const Contact & c)
    {
        os << "name: " << c.name << " address: " << *(c.address) << endl;
        return os;
    }

private:
    friend class serialization::access;

    template<typename archive>
    void serialize(archive & ar, const unsigned int ver)
    {
        ar & name;
        ar & address;
    }
};

struct EmployeeFactory
{
    static unique_ptr<Contact> new_main_office_employee(const string & name, const int suite)
    {
        static Contact p{"", new Address{"123 Est Drv", "London", 0}};
        return new_employee(name, suite, p);
    }

private:
    static unique_ptr<Contact> new_employee(const string & name, const int suite, const Contact & prototype)
    {
        auto result = make_unique<Contact>(prototype);
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};

int main()
{
    Contact john{"John Doe", new Address{"123 Est Drv", "London", 123}};
    Contact jane{"Jane Smith", new Address{"123 Est Drv", "London", 103}};
    Contact jane2 = john;
    jane2.name = "Jane Smith2";
    jane2.address->suite = 103;

    cout << john << endl << jane << endl << jane2 << endl;

    auto johnF = EmployeeFactory::new_main_office_employee("Jonn DoeFac", 123);
    cout << *johnF;

    auto clone = [](const Contact & c)
    {
        ostringstream oss;
        archive::text_oarchive oa(oss);
        oa << c;
        string s = oss.str();
        cout << "" << s << endl;

        istringstream iss(s);
        archive::text_iarchive ia(iss);
        Contact result;
        ia >> result;
        return result;
    };

    cout << endl << endl << endl;

    auto johnF2 = EmployeeFactory::new_main_office_employee("Jonn DoeFac2", 123);
    auto janeF2 = clone(*johnF2);

    cout << endl << endl << *johnF2 << endl;
    cout << janeF2 << endl;

    janeF2.address->suite = 103;

    cout << endl << endl << *johnF2 << endl;
    cout << janeF2 << endl;

    return 0;
}

//30
