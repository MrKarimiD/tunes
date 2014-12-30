#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "person.h"
#include "purchase_list.h"

class Customer : public Person
{
public:
    Customer();
    Customer(string name,string family_name,string password,string email);
    string showNotifications();
    string showNewNotifications();
    purchase_list purchase_history , purchase_basket;
    void addNewNotif(string input);
    void addNotif(string input);
    string customerInfo();

private:
    string email;
    vector<string> notifications;
    vector<string> new_notifications;
};

#endif // CUSTOMER_H
