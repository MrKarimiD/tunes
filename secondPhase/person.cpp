#include "person.h"

Person::Person()
{
}

Person::Person(string name, string family_name, string password, string role)
{
    this->name = name;
    this->family_name = family_name;
    this->password = password;
    this->role = role;
}

string Person::get_uname()
{
    return this->user_name;
}

string Person::get_password()
{
    return this->password;
}
