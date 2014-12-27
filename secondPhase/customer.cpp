#include "customer.h"

Customer::Customer()
{
}

Customer::Customer(string name, string family_name, string password, string email)
    :Person(name,family_name,password,"customer")
{
    this->email = email;
    this->user_name = this->email;
}
