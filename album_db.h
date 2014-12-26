#ifndef ALBUM_DB_H
#define ALBUM_DB_H

#include <fstream>
#include "album.h"
#include "vector"
#include "string"

class album_db
{
public:
    album_db();
    bool loadFromText(string file_name);
    bool saveToText(string file_name);
    void addNewAlbum(int id,string album_name,string singer,double price);
    void addNewTrack(int album_id,int track_num,string name,double duration,double price);
    void increaseEntity(int album_code,int number);
    void showAlbums();
    void showAlbumDetails(int album_id);

private:
    vector<Album> albums;
};

#endif // ALBUM_DB_H
