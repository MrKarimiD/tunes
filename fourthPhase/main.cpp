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
    cout<<"Welcome To Tunes - Third Phase\n";

    album_db albums;
    person_db persons;

    int login_person_id = -1;
    string login_person_name = "anonymous";

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
                        persons.addItemToBasket(login_person_id,item);
                    }
                    else if(tokens.size() == 3)
                    {
                        cout<<"Added to List\n";
                        string trackID_str = tokens.at(2);
                        purchase item(atoi(albumID_str.c_str()),atoi(trackID_str.c_str()));
                        persons.addItemToBasket(login_person_id,item);
                    }
                    else
                    {
                        cout<<"Wrong Pattern!\n";
                    }
                }
                else
                    cout<< "Error! : First start the purchase!\n";
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
                    std::ostringstream output;
                    purchase_list basket = persons.getBasket(login_person_id);
                    purchase_list history = persons.getHistory(login_person_id);
                    output << "User : "<<login_person_name << "\n";
                    if( login_person_id != -1)
                    {
                        output << albums.buyAndExportFactor(basket,history) << "\n";
                        persons.setBasket(login_person_id,basket);
                        persons.setHistory(login_person_id,history);
                        cout << output.str();
                    }
                    else
                    {
                        cout << "You should login to continue!\n";
                        cout << "Do you want to register (y/n) ? \n";
                        string ans;
                        getline(cin,ans);
                        if(ans == "y")
                        {
                            purchase_list past = persons.getBasket(login_person_id);
                            cout << "enter in this format :\n";
                            cout << "register name family email password\n";
                            ans.clear();
                            getline(cin,ans);

                            std::istringstream buf2(ans);
                            std::istream_iterator<string> beg2(buf2), end2;
                            vector<string> tokens2(beg2, end2);
                            string password;
                            password.append(tokens2.at(4));
                            for(int i=5;i<tokens2.size();i++)
                            {
                                password.append(" ");
                                password.append(tokens2.at(i));
                            }
                            string email = tokens2.at(3);
                            if( isValidEmailAddress(email.c_str()))
                            {
                                bool registerCheck = persons.reg_fun(tokens2.at(1),tokens2.at(2),tokens2.at(3),password
                                                                     ,login_person_name,login_person_id);
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

                            std::ostringstream output;
                            persons.setBasket(login_person_id,past);
                            purchase_list basket = persons.getBasket(login_person_id);
                            purchase_list history = persons.getHistory(login_person_id);
                            output << "User : "<<login_person_name << "\n";
                            if( login_person_id != -1)
                            {
                                output << albums.buyAndExportFactor(basket,history) << "\n";
                                persons.setBasket(login_person_id,basket);
                                persons.setHistory(login_person_id,history);
                                cout << output.str();
                            }
                        }
                        else if(ans == "n")
                        {
                            output << albums.exportFactor(persons.getBasket(login_person_id)) << "\n";
                            cout << output.str();
                        }
                    }
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
                if( login_person_id != -1)
                {
                    for(int i=0;i<persons.historySize(login_person_id);i++)
                    {
                        purchase item = persons.getItemFromHistory(login_person_id,i);//purchase_history.list.at(i);

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
                else
                    cout << "Anonymous users don't have any history!\n";
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
                bool registerCheck = persons.reg_fun(tokens.at(1),tokens.at(2),tokens.at(3),password
                                                     ,login_person_name,login_person_id);
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
            if( tokens.at(1) != "anonymous" )
            {
                string password = tokens.at(2);
                for(int i=3;i<tokens.size();i++)
                {
                    password.append(" ");
                    password.append(tokens.at(i));
                }
                role = persons.login(tokens.at(1),password,login_person_name,login_person_id);
            }
            else
            {
                login_person_id = -1;
                login_person_name = "anonymous";
                role = "customer";
            }
            cout << "role:"<<role << "\n";
        }
        else if(tokens.at(0) == "logout" )
        {
            role = "unknown";
            purchase_status = "nothing";
        }
        else if(tokens.at(0) == "report_purchases")
        {
            if( login_person_name == "Admin")
            {
                std::ostringstream history;
                int sumOfAll = 0;
                int sumOfEach = 0;
                for(int j=0;j<persons.numberOfCustomers();j++)
                {
                    history <<"Customer : "<<persons.getCustomerName(j)<<"\n";
                    for(int i=0;i<persons.historySize(j);i++)
                    {
                        purchase item = persons.getItemFromHistory(j,i);

                        if(item.get_track_id() == 0)
                        {
                            history << albums.findAlbumInfo(item.get_album_id())<<"\n";
                            sumOfEach += albums.findAlbumPrice(item.get_album_id());
                        }
                        else
                        {
                            history << albums.findTrackInfo(item.get_album_id(),item.get_track_id())<<"\n";
                            sumOfEach += albums.findTrackPrice(item.get_album_id(),item.get_track_id());
                        }
                    }
                    history << "Cost :" << sumOfEach << "\n";
                    sumOfAll += sumOfEach;
                    history <<"----------------------\n";
                }
                history << "Total Cost : "<<sumOfAll <<"\n";
                cout << history.str();
            }
            else
            {
                cout<<"You don't have enough permission!\n";
            }
        }
        else if(tokens.at(0) == "show_basket_contents")
        {
            std::ostringstream output;
            output << albums.exportFactor(persons.getBasket(login_person_id)) << "\n";
            cout << output.str();
        }
        else if(tokens.at(0) == "delete_purchase")
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
                        cout<<"Removed from List\n";
                        persons.removeItemFromBasket(login_person_id,atoi(albumID_str.c_str()),0);
                    }
                    else if(tokens.size() == 3)
                    {
                        cout<<"Removed from List\n";
                        string trackID_str = tokens.at(2);
                        persons.removeItemFromBasket(login_person_id,atoi(albumID_str.c_str()),atoi(trackID_str.c_str()));
                    }
                    else
                    {
                        cout<<"Wrong Pattern!\n";
                    }
                }
            }
        }
        else
            cout<<"Unknown Command!\n";
    }
}
