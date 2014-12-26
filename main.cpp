#include "iostream"
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Welcome To Tunes\n";

    ofstream albums_file;
    albums_file.open("albums.txt");
    cout<<"Album's File Loaded Correctly.\n";

    string role = "Customer";

    string cmd;
    while(true)
    {
        cout<<"Enter your Commands : \n";

        cin>>cmd;

        if( cmd.compare("‫‪employee‬‬") == 0 )
        {
            cout<<"Role switched to ‫‪Employee‬‬";
            role = "‫‪employee‬‬";
        }
    }
}
