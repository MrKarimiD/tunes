#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "person.h"
#include "purchase_list.h"

class Customer : public Person
{
public:
    Customer();
    Customer(string name,string family_name,string password,string email);

    purchase_list purchase_history , purchase_basket;

private:
    string email;
};

#endif // CUSTOMER_H
