#ifndef PERSON_H
#define PERSON_H

#include "iostream";

using namespace std;

class Person
{
public:
    Person();

private:
    string name;
    string family_name;
    string email;
    string password;
    string role;
};

#endif // PERSON_H
