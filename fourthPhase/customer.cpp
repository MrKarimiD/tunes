#include "customer.h"

Customer::Customer()
{
}

Customer::Customer(string name, string family_name, string password, string email)
    :Person(name,family_name,password,"customer")
{
    this->email = email;
    this->user_name = this->email;
    this->numberOfNewNotifications = 0;
}

string Customer::showNotifications()
{
    std::ostringstream output;
    output << "You have " << numberOfNewNotifications <<" new messages!\n";
    output << new_notifications;
    output << notifications;
    numberOfNewNotifications = 0;
    notifications.append(new_notifications);
    new_notifications.clear();
    return output.str();
}

string Customer::showNewNotifications()
{
    std::ostringstream output;
    output << "You have " << numberOfNewNotifications <<" new messages!\n";
    output << new_notifications;
    numberOfNewNotifications = 0;
    notifications.append(new_notifications);
    new_notifications.clear();
    return output.str();
}

void Customer::addNewNotif(string input)
{
    numberOfNewNotifications++;
    new_notifications.append(input);
    new_notifications.append("\n");
}
