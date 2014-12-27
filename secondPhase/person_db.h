#ifndef PERSON_DB_H
#define PERSON_DB_H

#include "staff.h"
#include "customer.h"
#include <vector>

class person_db
{
public:
    person_db();

private:
   vector<Staff> staffs;
   vector<Customer> customers;
};

#endif // PERSON_DB_H
