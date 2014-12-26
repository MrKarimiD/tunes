#ifndef TRACK_H
#define TRACK_H
#include "iostream"
#include <sstream>

using namespace std;

class Track
{
public:
    Track();
    string trackDetails();

private:
   int index;
   int album_code;
   string name;
   double duration;
   double price;
};

#endif // TRACK_H
