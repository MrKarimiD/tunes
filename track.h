#ifndef TRACK_H
#define TRACK_H
#include "iostream"
#include <sstream>

using namespace std;

class Track
{
public:
    Track();
    Track(int album_code,int index,string name,double duration,double price);
    string trackDetails();
    double trackPrice();
    string trackName();

private:
   int index;
   int album_code;
   string name;
   double duration;
   double price;
};

#endif // TRACK_H
