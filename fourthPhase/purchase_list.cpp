#include "purchase_list.h"

purchase_list::purchase_list()
{
}

string purchase_list::show_list()
{
    std::stringstream out;

    for(int i=0;i<list.size();i++)
    {
        purchase temp = list.at(i);
        out << temp.show()<<"\n";
    }

    return out.str();
}

void purchase_list::addPurchaseItem(purchase newItem)
{
    if( ! isInList(newItem) )
    {
        list.push_back(newItem);
    }
    else
    {
        cout << "Already in your list!";
    }
}

void purchase_list::removeItem(int album_id, int track_id)
{
    for(int i=0;i<list.size();i++)
    {
        purchase temp = list.at(i);
        if(album_id == temp.get_album_id() )
        {
            if( track_id == temp.get_track_id() )
            {
                vector<purchase>::iterator iter = list.begin() + i;
                list.erase(iter);
            }
            else
            {
                cout << "Warning : Entity Not Found!";
            }
        }
    }
}

bool purchase_list::isInList(purchase item)
{
    for(int i=0;i<list.size();i++)
    {
        purchase temp = list.at(i);

        if( item.get_album_id() == temp.get_album_id() )
        {
            if( item.get_track_id() == temp.get_track_id() )
                return true;
            else if( temp.get_track_id() == 0 )
                return true;
        }
    }
    return false;
}
