#include <iostream>
#include <string>
#include <vector>
using namespace std;

class PersonBuilder;
class PersonJobBuilder;
class PersonAdressBuilder;

class Person
{
    //adress
    string street_address, post_code, city;

    //employment
    string company_name, position;
    int annual_income{0};

public:
    static PersonBuilder create();
    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAdressBuilder;
    friend ostream & operator<<(ostream & os, const Person & person);
};

class PersonBuilderBase
{
protected:
    Person & person;
public:
    PersonBuilderBase(Person & p) : person(p){}

    PersonAdressBuilder lives() const;
    PersonJobBuilder works() const;

    operator Person(){
        return move(person);
    }
};

class PersonAdressBuilder : public PersonBuilderBase
{
    using Self = PersonAdressBuilder;
public:
    explicit PersonAdressBuilder(Person & p) : PersonBuilderBase(p){}
    PersonAdressBuilder & at(string street_adress)
    {
        person.street_address = street_adress;
        return *this;
    }

    PersonAdressBuilder & with_postcode(string postcode)
    {
        person.post_code = postcode;
        return *this;
    }

    PersonAdressBuilder & in(string city)
    {
        person.city = city;
        return * this;
    }
};

class PersonJobBuilder : public PersonBuilderBase
{
public:
    explicit PersonJobBuilder(Person & p) : PersonBuilderBase(p){}
    PersonJobBuilder & at(string companyname)
    {
        person.company_name = companyname;
        return *this;
    }

    PersonJobBuilder & as_a(string position)
    {
        person.position = position;
        return * this;
    }

    PersonJobBuilder &  earning(int val)
    {
        person.annual_income = val;
        return * this;
    }
};


PersonAdressBuilder PersonBuilderBase::lives() const
{
    return PersonAdressBuilder(person);
}

PersonJobBuilder PersonBuilderBase::works() const
{
    return PersonJobBuilder(person);
}

class PersonBuilder : public PersonBuilderBase
{
    Person p;
public:
    PersonBuilder() : PersonBuilderBase(p){}
};

PersonBuilder Person::create()
{
    return PersonBuilder();
}

ostream & operator<<(ostream & os, const Person & person)
{
    os << "street_address: " << person.street_address << endl;
    os << "post_code: " << person.post_code << endl;
    os << "city: " << person.city << endl;
    os << "company_name: " << person.company_name << endl;
    os << "position: " << person.position << endl;
    os << "annual_income: " << person.annual_income << endl;
    return os;
}

int main()
{
    Person p = Person::create()
            .lives().at("123 London Road").with_postcode("SW1 1GB").in("London")
            .works().at("PragmaSoft").as_a("Consultant").earning(100);

    cout << p << endl;

    return 0;
}

