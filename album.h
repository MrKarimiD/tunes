#ifndef ALBUM_H
#define ALBUM_H

#include "track.h"
#include <vector>

class Album
{
public:
    Album();
    Album(int id,string albumName,string singerName,double price);
    string albumDetails();
    void addNewTrack(int index,string name,double duration,double price);
    string albumStatus();
    int getAlbumID();
    void increase(int value);
    bool isAvailable();
    double buy();
    string getAlbumName();
    double getAlbumPrice();
    string findTrackInfo(int track_id);
    double findTrackPrice(int track_id);

private:
    string status();

private:
    vector<Track> tracks;
    int numberOfAvailable;
    int id;
    string singerName;
    string albumName;
    double price;
};

#endif // ALBUM_H
