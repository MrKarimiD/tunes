#ifndef PURCHASE_H
#define PURCHASE_H

#include <iostream>
#include <sstream>
using namespace std;

class purchase
{
public:
    purchase();
    purchase(int album_id,int track_id);
    string show();
    int get_album_id();
    int get_track_id();
    void set_status(string status);
    string get_status();

private:
    int album_id;
    int track_id;
    string status;
};

#endif // PURCHASE_H
