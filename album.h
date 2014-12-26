#ifndef ALBUM_H
#define ALBUM_H

#include "track.h"
#include <vector>

class Album
{
public:
    Album();
    string albumDetails();

private:
    vector<Track> tracks;
    int numberOfAvailable;
    int id;
    string singerName;
    string albumName;
    double price;
};

#endif // ALBUM_H
