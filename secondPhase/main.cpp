#include "iostream"
#include <fstream>
#include <sstream>
#include "album_db.h"
#include "purchase_list.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Welcome To Tunes - First Phase\n";

    album_db albums;
    purchase_list purchase_history , purchase_tempList;

    bool loadCorrectly = albums.loadFromText("albums.txt");
    if(loadCorrectly)
        cout<<"Album's File Loaded Correctly.\n";
    else
    {
        cout<<"Error : Album's File didn't load corectly!";
        return 0;
    }

    string role = "customer";

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
            if( role == "‫‪employee‬‬")
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
            if( role == "‫‪employee‬‬")
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
            if( role == "‫‪employee‬‬")
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
            purchase_status = "start";
            cout<<"Purchase Started\n";
        }
        else if(tokens.at(0) == "show_albums" )
        {
            cout<<albums.showAlbums()<<"\n";
        }
        else if(tokens.at(0) == "show_album" )
        {
            string albumID_str = tokens.at(1);
            cout<<albums.showAlbumDetails(atoi(albumID_str.c_str()));
        }
        else if(tokens.at(0) == "purchase" )
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
        else if(tokens.at(0) == "end_purchase" )
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
        else if(tokens.at(0) == "show_all_purchases" )
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
        else if(tokens.at(0) == "quit" )
        {
            bool saveCorrectly = albums.saveToText("albums.txt");
            if( saveCorrectly )
                cout << "Data saved correctly.\n";

            else
                cout << "There is a problem for saving data.\n";

            return 0;
        }
        else
            cout<<"Unknown Command!\n";

    }
}
