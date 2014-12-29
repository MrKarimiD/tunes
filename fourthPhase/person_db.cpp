#include "person_db.h"

person_db::person_db()
{
     anonymous = new Customer("anonymous","","","");
}

bool person_db::loadStaffsFromText(string inputName)
{
    ifstream textFile;
    textFile.open(inputName.data());

    staffs.clear();

    if (textFile.is_open())
    {
        string line;
        while ( getline(textFile,line) )
        {
            std::istringstream buf(line);
            std::istream_iterator<string> beg(buf), end;
            vector<string> tokens(beg, end);

            string password = tokens.at(3);
            for(int i=4;i<tokens.size();i++)
            {
                password.append(" ");
                password.append(tokens.at(i));
            }
            Staff temp(tokens.at(0),tokens.at(1),password,tokens.at(2));
            staffs.push_back(temp);
        }

        Staff admin("Admin","Admin","Admin","Admin");
        staffs.push_back(admin);

        textFile.close();
        return true;
    }

    textFile.close();
    return false;
}

void person_db::addToPerson(string name, string family_name, string email, string password)
{
    Customer temp(name,family_name,password,email);
    customers.push_back(temp);
}

string person_db::login(string uname, string password, string &name, int &id)
{
    string role = "unknown";
    id = -1;
    name = "anonymous";

    for(int i=0;i<staffs.size();i++)
    {
        Staff temp = staffs.at(i);
        if( ( temp.get_uname() == uname) && (temp.get_password() == password) )
        {
            id = i;
            name = temp.get_uname();
            role = "staff";
            break;
        }
    }

    if(role == "unknown")
    {
        for(int i=0;i<customers.size();i++)
        {
            Customer temp = customers.at(i);
            if( ( temp.get_uname() == uname) && (temp.get_password() == password) )
            {
                id = i;
                name = temp.get_uname();
                role = "customer";
                break;
            }
        }
    }

    return role;
}

bool person_db::reg_fun(string name, string family_name, string email, string password, string &log_name, int &id)
{
    log_name = "anonymous";
    id = -1;

    Customer temp(name,family_name,email,password);

    for(int i=0;i<customers.size();i++)
    {
        if(temp.get_uname() == email)
            return false;
    }

    addToPerson(name,family_name,email,password);
    log_name = email;
    id = customers.size()-1;
    return true;
}

void person_db::addItemToBasket(int person_id, purchase item)
{
    Customer *temp;
    if(person_id != -1)
    {
        temp = &customers.at(person_id);
    }
    else
    {
        temp = anonymous;
    }
    temp->purchase_basket.addPurchaseItem(item);
}

void person_db::addToHistory(int person_id, purchase item)
{
    Customer *temp;
    if(person_id != -1)
    {
        temp = &customers.at(person_id);
        temp->purchase_history.addPurchaseItem(item);
    }
}

int person_db::basketSize(int person_id)
{
    Customer *temp;
    if(person_id != -1)
    {
        temp = &customers.at(person_id);
    }
    else
    {
        temp = anonymous;
    }

    return temp->purchase_basket.list.size();
}

int person_db::historySize(int person_id)
{
    Customer *temp;
    if(person_id != -1)
    {
        temp = &customers.at(person_id);
    }
    else
    {
        temp = anonymous;
    }

    return temp->purchase_history.list.size();
}

bool person_db::clearBasket(int person_id)
{
    bool clearIt;
    Customer *temp;
    if(person_id != -1)
    {
        temp = &customers.at(person_id);
        temp->purchase_basket.list.clear();
        clearIt = true;
    }
    else
    {
        cout<<"You should login to continue!\n";
        cout<<"Do you want to login ?(Y/n)\n";
        clearIt = false;
    }
    return clearIt;
}

purchase person_db::getItemFromBasket(int person_id, int item_id)
{
    Customer *temp;
    if(person_id != -1)
    {
        temp = &customers.at(person_id);
    }
    else
    {
        temp = anonymous;
    }

    return temp->purchase_basket.list.at(item_id);
}

purchase person_db::getItemFromHistory(int person_id, int item_id)
{
    Customer *temp;
    if(person_id != -1)
    {
        temp = &customers.at(person_id);
    }
    else
    {
        temp = anonymous;
    }

    return temp->purchase_history.list.at(item_id);
}

int person_db::numberOfCustomers()
{
    return this->customers.size();
}

string person_db::getCustomerName(int person_id)
{
    Customer *temp;
    if(person_id != -1)
    {
        temp = &customers.at(person_id);
    }
    else
    {
        temp = anonymous;
    }

    return temp->get_uname();
}

void person_db::removeItemFromBasket(int person_id, int album_id, int track_id)
{
    Customer *temp;
    if(person_id != -1)
    {
        temp = &customers.at(person_id);
    }
    else
    {
        temp = anonymous;
    }

    temp->purchase_basket.removeItem(album_id,track_id);
}

purchase_list person_db::getBasket(int person_id)
{
    Customer *temp;
    if(person_id != -1)
    {
        temp = &customers.at(person_id);
    }
    else
    {
        temp = anonymous;
    }

    return temp->purchase_basket;
}

purchase_list person_db::getHistory(int person_id)
{
    Customer *temp;
    if(person_id != -1)
    {
        temp = &customers.at(person_id);
    }
    else
    {
        temp = anonymous;
    }

    return temp->purchase_history;
}

void person_db::setBasket(int person_id, purchase_list input)
{
    Customer *temp;
    if(person_id != -1)
    {
        temp = &customers.at(person_id);
    }
    else
    {
        temp = anonymous;
    }

    temp->purchase_basket = input;
}

void person_db::setHistory(int person_id, purchase_list input)
{
    Customer *temp;
    if(person_id != -1)
    {
        temp = &customers.at(person_id);
    }
    else
    {
        temp = anonymous;
    }

    temp->purchase_history.list.clear();
    temp->purchase_history = input;
}
