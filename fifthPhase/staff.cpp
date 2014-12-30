#include "staff.h"

Staff::Staff()
{
}

Staff::Staff(string name, string family_name, string password, string phone_number)
    : Person(name, family_name,password,"Staff")
{
    this->phone_number = phone_number;
    this->user_name = this->phone_number;
}
