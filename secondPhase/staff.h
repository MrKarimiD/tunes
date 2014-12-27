#ifndef STAFF_H
#define STAFF_H

#include "person.h"

class Staff : public Person
{
public:
    Staff();

private:
    string phone_number;
};

#endif // STAFF_H
