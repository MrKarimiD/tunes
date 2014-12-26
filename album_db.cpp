#include "album_db.h"

album_db::album_db()
{
}

bool album_db::loadFromText(string file_name)
{
    ifstream textFile;
    textFile.open(file_name.data());

    if (textFile.is_open())
    {
        while (!textFile.eof())
        {
        }
        return true;
    }
    else
    {
        return false;
    }
    textFile.close();
}

bool album_db::saveToText(string file_name)
{
    ofstream textFile;
    textFile.open(file_name.data());

    if (textFile.is_open())
    {
        std::stringstream out;

        for(int i=0;i<albums.size();i++)
        {
            Album temp = albums.at(i);
            out <<temp.albumDetails();
        }
        textFile<<out.str();
    }
    else
    {
        return false;
    }

    textFile.close();
}

void album_db::addNewAlbum(int id, string album_name, string singer, double price)
{

}

void album_db::addNewTrack(int album_id, int track_num, string name, double duration, double price)
{

}

void album_db::increaseEntity(int album_code, int number)
{

}

void album_db::showAlbums()
{

}

void album_db::showAlbumDetails(int album_id)
{

}
