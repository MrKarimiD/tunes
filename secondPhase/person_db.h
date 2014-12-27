#ifndef PERSON_DB_H
#define PERSON_DB_H

#include "staff.h"
#include "customer.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class person_db
{
public:
    person_db();
    bool loadStaffsFromText(string inputName);
    void addToPerson(string name,string family_name,string email,string password);
    string login(string uname,string password);
    bool reg_fun(string name,string family_name,string email,string password);
private:
   vector<Staff> staffs;
   vector<Customer> customers;
};

#endif // PERSON_DB_H
