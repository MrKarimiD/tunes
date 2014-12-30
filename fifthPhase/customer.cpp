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

string Customer::showNotifications()
{
    std::ostringstream output;
    output << "You have " << new_notifications.size() <<" new messages!\n";
    for(int i=0;i<new_notifications.size();i++)
    {
        output << new_notifications.at(i) << "\n";
    }
    for(int i=0;i<notifications.size();i++)
    {
        output << notifications.at(i) << "\n";
    }

    for(int i=0;i<new_notifications.size();i++)
    {
        notifications.push_back(new_notifications.at(i));
    }
    new_notifications.clear();
    return output.str();
}

string Customer::showNewNotifications()
{
    std::ostringstream output;
    output << "You have " << new_notifications.size() <<" new messages!\n";
    for(int i=0;i<new_notifications.size();i++)
    {
        output << new_notifications.at(i) << "\n";
    }

    for(int i=0;i<new_notifications.size();i++)
    {
        notifications.push_back(new_notifications.at(i));
    }
    new_notifications.clear();
    return output.str();
}

void Customer::addNewNotif(string input)
{
    new_notifications.push_back(input);
}

void Customer::addNotif(string input)
{
    notifications.push_back(input);
}

string Customer::customerInfo()
{
    std::ostringstream output;
    output << this->name << " " << this->family_name << " " << this->email << " " << this->password << "\n";
    for(int i=0;i<purchase_basket.list.size();i++)
    {
        purchase tmp = purchase_basket.list.at(i);
        output << "+ "<< tmp.get_album_id() << " " << tmp.get_track_id() << " " << tmp.get_status() << "\n";
    }
    for(int i=0;i<purchase_history.list.size();i++)
    {
        purchase tmp = purchase_history.list.at(i);
        output << "- "<< tmp.get_album_id() << " " << tmp.get_track_id() << " " << tmp.get_status() << "\n";
    }
    for(int i=0;i<notifications.size();i++)
    {
        output << "* "<< notifications.at(i) << "\n";
    }
    for(int i=0;i<new_notifications.size();i++)
    {
        output << "$ "<< new_notifications.at(i) << "\n";
    }
    return output.str();
}
