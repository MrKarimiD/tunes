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

private:
    int album_id;
    int track_id;
};

#endif // PURCHASE_H
