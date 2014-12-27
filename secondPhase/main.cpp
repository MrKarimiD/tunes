#include <iostream>
#include <fstream>
#include <sstream>
#include "album_db.h"
#include "purchase_list.h"
#include "person_db.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

bool isCharacter(const char Character)
{
    return ( (Character >= 'a' && Character <= 'z') || (Character >= 'A' && Character <= 'Z'));
}

bool isNumber(const char Character)
{
    return ( Character >= '0' && Character <= '9');
}

bool isValidEmailAddress(string EmailAddress)
{
    if(!isCharacter(EmailAddress.at(0)))
        return 0;
    int AtOffset = -1;
    int DotOffset = -1;
    if( (EmailAddress.at(EmailAddress.size()-1) == 'm') && (EmailAddress.at(EmailAddress.size()-2) == 'o') &&
            (EmailAddress.at(EmailAddress.size()-3) == 'c') && (EmailAddress.at(EmailAddress.size()-4) == '.') )
    {
        unsigned int Length = EmailAddress.length();
        for(int i = 0; i < Length; i++)
        {
            if(EmailAddress.at(i) == '@')
                AtOffset = (int)i;
        }

        EmailAddress.erase(EmailAddress.end()-4,EmailAddress.end());
        string first = EmailAddress.substr(0,AtOffset);
        string second = EmailAddress.substr(AtOffset,EmailAddress.size());

        if( !first.empty() && !second.empty())
            return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    cout<<"Welcome To Tunes - First Phase\n";

    album_db albums;
    person_db persons;
    purchase_list purchase_history , purchase_tempList;

    bool loadAlbumsCorrectly = albums.loadFromText("albums.txt");
    if(loadAlbumsCorrectly)
        cout<<"Album's File Loaded Correctly.\n";
    else
    {
        cout<<"Error : Album's File didn't load corectly!";
        return 0;
    }

    bool loadStaffCorrectly = persons.loadStaffsFromText("staff.txt");
    if(loadStaffCorrectly)
        cout<<"Staff's File Loaded Correctly.\n";
    else
    {
        cout<<"Error : Staff's File didn't load corectly!";
        return 0;
    }

    string role = "unknown";
    string purchase_status = "nothing";

    while(true)
    {
        cout<<"Enter your Commands : \n";

        string cmd;
        getline(cin,cmd);
        std::istringstream buf(cmd);
        std::istream_iterator<string> beg(buf), end;
        vector<string> tokens(beg, end);

        if(tokens.at(0) == "add_album")
        {
            if( role == "staff")
            {
                string id_str = tokens.at(1) ,price_str = tokens.at(4);
                albums.addNewAlbum(atoi(id_str.c_str()),tokens.at(2),tokens.at(3),atof(price_str.c_str()));
            }
            else
            {
                cout << "You don't Have This Permission!\n";
            }
        }
        else if(tokens.at(0) == "add_song")
        {
            if( role == "staff")
            {
                string albumCode_str = tokens.at(1) ,trackID_str = tokens.at(2) , dur_str = tokens.at(4) , price_str = tokens.at(5);
                albums.addNewTrack(atoi(albumCode_str.c_str()),atoi(trackID_str.c_str()),tokens.at(3),atof(dur_str.c_str()),atof(price_str.c_str()));
            }
            else
            {
                cout << "You don't Have This Permission!\n";
            }
        }
        else if(tokens.at(0) == "increase_entity")
        {
            if( role == "staff")
            {
                string albumID_str = tokens.at(0) , num_str = tokens.at(1) ;
                albums.increaseEntity(atoi(albumID_str.c_str()),atoi(num_str.c_str()));
            }
            else
            {
                cout << "You don't Have This Permission!\n";
            }
        }
        else if(tokens.at(0) == "start_purchase" )
        {
            if(role == "unknown")
            {
                cout << "Please Log in!";
            }
            else
            {
                purchase_status = "start";
                cout<<"Purchase Started\n";
            }
        }
        else if(tokens.at(0) == "show_albums" )
        {
            if(role == "unknown")
            {
                cout << "Please Log in!";
            }
            else
            {
                cout<<albums.showAlbums()<<"\n";
            }
        }
        else if(tokens.at(0) == "show_album" )
        {
            if(role == "unknown")
            {
                cout << "Please Log in!";
            }
            else
            {
                string albumID_str = tokens.at(1);
                cout<<albums.showAlbumDetails(atoi(albumID_str.c_str()));
            }
        }
        else if(tokens.at(0) == "purchase" )
        {
            if(role == "unknown")
            {
                cout << "Please Log in!";
            }
            else
            {
                if(purchase_status == "start")
                {
                    string albumID_str = tokens.at(1);
                    if(tokens.size() == 2)
                    {
                        cout<<"Added to List\n";
                        purchase item(atoi(albumID_str.c_str()),0);
                        purchase_tempList.addPurchaseItem(item);
                    }
                    else if(tokens.size() == 3)
                    {
                        cout<<"Added to List\n";
                        string trackID_str = tokens.at(2);
                        purchase item(atoi(albumID_str.c_str()),atoi(trackID_str.c_str()));
                        purchase_tempList.addPurchaseItem(item);
                    }
                    else
                    {
                        cout<<"Wrong Pattern!\n";
                    }
                }
            }
        }
        else if(tokens.at(0) == "end_purchase" )
        {
            if(role == "unknown")
            {
                cout << "Please Log in!";
            }
            else
            {
                if(purchase_status == "start")
                {
                    std::ostringstream factor;
                    double cost =0;
                    for(int i=0;i<purchase_tempList.list.size();i++)
                    {
                        purchase item = purchase_tempList.list.at(i);

                        if(albums.isAvailable(item.get_album_id()))
                        {
                            if(item.get_track_id() == 0)
                            {
                                albums.buyAlbum(item.get_album_id());
                                factor << albums.findAlbumInfo(item.get_album_id())<<"\n";
                                cost = cost + albums.findAlbumPrice(item.get_album_id());
                            }
                            else
                            {
                                albums.buyTrack(item.get_album_id(),item.get_track_id());
                                factor << albums.findTrackInfo(item.get_album_id(),item.get_track_id())<<"\n";
                                cost = cost + albums.findTrackPrice(item.get_album_id(),item.get_track_id());
                            }
                            purchase_history.list.push_back(item);
                        }
                    }
                    factor <<"\nTotal Price : "<<cost;
                    cout << factor.str()<<"\n";
                    purchase_tempList.list.clear();
                    purchase_status = "nothing";
                }
            }
        }
        else if(tokens.at(0) == "show_all_purchases" )
        {
            if(role == "unknown")
            {
                cout << "Please Log in!";
            }
            else
            {
                std::ostringstream history;
                for(int i=0;i<purchase_history.list.size();i++)
                {
                    purchase item = purchase_history.list.at(i);

                    if(item.get_track_id() == 0)
                    {
                        history << albums.findAlbumInfo(item.get_album_id())<<"\n";
                    }
                    else
                    {
                        history << albums.findTrackInfo(item.get_album_id(),item.get_track_id())<<"\n";
                    }
                }
                cout << history.str();
            }
        }
        else if(tokens.at(0) == "quit" )
        {
            bool saveCorrectly = albums.saveToText("albums.txt");
            if( saveCorrectly )
                cout << "Data saved correctly.\n";

            else
                cout << "There is a problem for saving data.\n";

            return 0;
        }
        else if(tokens.at(0) == "register" )
        {
            string password;
            password.append(tokens.at(4));
            for(int i=5;i<tokens.size();i++)
            {
                password.append(" ");
                password.append(tokens.at(i));
            }
            string email = tokens.at(3);
            if( isValidEmailAddress(email.c_str()))
            {
                bool registerCheck = persons.reg_fun(tokens.at(1),tokens.at(2),tokens.at(3),password);
                if(registerCheck)
                {
                    cout << "User added successfully\n";
                    role = "customer";
                }
                else
                    cout << "User can't added to System\n";
            }
            else
            {
                cout << "Email foramt isn't corrected\n";
            }
        }
        else if(tokens.at(0) == "login" )
        {
            string password = tokens.at(2);
            for(int i=3;i<tokens.size();i++)
            {
                password.append(" ");
                password.append(tokens.at(i));
            }
            role = persons.login(tokens.at(1),password);
            cout << "role:"<<role;
        }
        else if(tokens.at(0) == "logout" )
        {
            role = "unknown";
            purchase_history.list.clear();
            purchase_tempList.list.clear();
            purchase_status = "nothing";
        }
        else
            cout<<"Unknown Command!\n";
    }
}
