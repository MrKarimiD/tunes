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

    //cout << albums.showAlbums();
    string role = "customer";

    while(true)
    {
        cout<<"Enter your Commands : \n";

        string cmd;
        getline(cin,cmd);
        std::istringstream buf(cmd);
        std::istream_iterator<string> beg(buf), end;
        vector<string> tokens(beg, end);

        if( tokens.at(0) == "employee")
        {
            cout<<"Role switched to ‫‪Employee\n‬‬";
            role = "‫‪employee‬‬";
        }
        else if(tokens.at(0) == "add_album")
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
                //Write It!
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
                //Write It!
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
            //Write It!
        }
        else
            cout<<"Unknown Command!\n";

    }
}
