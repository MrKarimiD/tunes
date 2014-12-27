#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "person.h"

class Customer : public Person
{
public:
    Customer();

private:
    string email;
};

#endif // CUSTOMER_H
