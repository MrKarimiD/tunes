#ifndef PERSON_H
#define PERSON_H

#include "iostream"
using namespace std;

class Person
{
public:
    Person();

protected:
    string name;
    string family_name;
    string user_name;
    string password;
    string role;
};

#endif // PERSON_H
