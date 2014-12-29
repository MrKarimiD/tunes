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
    string login(string uname,string password,string &name,int &id);
    bool reg_fun(string name, string family_name, string email, string password, string &log_name, int &id);
    void addItemToBasket(int person_id,purchase item);
    void addToHistory(int person_id,purchase item);
    int basketSize(int person_id);
    int historySize(int person_id);
    bool clearBasket(int person_id);
    purchase getItemFromBasket(int person_id,int item_id);
    purchase getItemFromHistory(int person_id,int item_id);
    int numberOfCustomers();
    string getCustomerName(int person_id);
    void removeItemFromBasket(int person_id,int album_id,int track_id);
    purchase_list getBasket(int person_id);
    purchase_list getHistory(int person_id);
    void setBasket(int person_id,purchase_list input);
    void setHistory(int person_id,purchase_list input);
    void notifyEveryOne(int album_id,string album_name);
    string show_notification(int person_id);
    string show_new_notification(int person_id);

    Customer *anonymous;

private:
   vector<Staff> staffs;
   vector<Customer> customers;
};

#endif // PERSON_DB_H
