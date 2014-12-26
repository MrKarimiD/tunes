#ifndef ALBUM_H
#define ALBUM_H

#include "track.h"

class Album
{
public:
    Album();

private:
    Track tracks[];
    int numberOfAvailable;
    int id;
    string singerName;
    double price;
};

#endif // ALBUM_H
