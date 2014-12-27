#ifndef STAFF_H
#define STAFF_H

#include "person.h"

class Staff : public Person
{
public:
    Staff();
    Staff(string name,string family_name,string password,string phone_number);

private:
    string phone_number;
};

#endif // STAFF_H
