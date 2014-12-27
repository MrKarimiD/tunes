#include "person_db.h"

person_db::person_db()
{
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

            Staff temp(tokens.at(0),tokens.at(1),tokens.at(2),tokens.at(3));
            staffs.push_back(temp);
        }

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

string person_db::login(string uname, string password)
{
    string role = "unknown";

    for(int i=0;i<staffs.size();i++)
    {
        Staff temp = staffs.at(i);
        if( ( temp.get_uname() == uname) && (temp.get_password() == password) )
        {
            role = "staff";
            break;
        }
    }

    for(int i=0;i<customers.size();i++)
    {
        Customer temp = customers.at(i);
        if( ( temp.get_uname() == uname) && (temp.get_password() == password) )
        {
            role = "customer";
            break;
        }
    }

    return role;
}

bool person_db::reg_fun(string name, string family_name, string email, string password)
{
    Customer temp(name,family_name,email,password);

    for(int i=0;i<customers.size();i++)
    {
        if(temp.get_uname() == email)
            return false;
    }

    addToPerson(name,family_name,email,password);
    return true;
}
