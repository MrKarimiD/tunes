#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "person.h"

class Customer : public Person
{
public:
    Customer();
    Customer(string name,string family_name,string password,string email);

private:
    string email;
};

#endif // CUSTOMER_H
