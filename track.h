#ifndef TRACK_H
#define TRACK_H
#include "iostream"
using namespace std;

class Track
{
public:
    Track();

private:
   int index;
   int album_code;
   string name;
   double duration;
   double price;
};

#endif // TRACK_H
