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

    cout << albums.showAlbums();
//    string role = "customer";

//    string cmd;
//    while(true)
//    {
//        cout<<"Enter your Commands : \n";

//        cin>>cmd;

//        if( cmd.compare("‫‪employee‬‬") == 0 )
//        {
//            cout<<"Role switched to ‫‪Employee‬‬";
//            role = "‫‪employee‬‬";
//        }
//    }
}
