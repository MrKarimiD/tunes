#include "iostream"
#include <fstream>

#include "album_db.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Welcome To Tunes\n";

    album_db albums;
    bool loadCorrectly = albums.loadFromText("albums.txt");
    if(loadCorrectly)
        cout<<"Album's File Loaded Correctly.\n";
    else
    {
        cout<<"Error : Album's File didn't load corectly!";
        return 0;
    }

    string role = "customer";

    if( strcmp(argv[1],"employee") == 0 )
    {
        cout<<"Role switched to ‫‪Employee\n‬‬";
        role = "‫‪employee‬‬";
    }

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
        else if(tokens.at(0) == "‫‪increase_entity‬‬")
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
        else if(tokens.at(0) == "‫‫‪start_purchase‬‬‬‬")
        {
            //Write It!
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
            //Write It!
        }
        else if(tokens.at(0) == "start_purchase" )
        {
            //Write It!
        }
        else if(tokens.at(0) == "end_purchase" )
        {
            //Write It!
        }
        else if(tokens.at(0) == "show_all_purchases" )
        {
            //Write It!
        }
        else if(tokens.at(0) == "quit" )
        {
            //Save & Quit
        }
        else
            cout<<"Unknown Command!\n";

    }
}
