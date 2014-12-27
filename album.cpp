#include "album.h"

Album::Album()
{
}

Album::Album(int id, string albumName, string singerName, double price)
{
    this->id = id;
    this->albumName = albumName;
    this->singerName = singerName;
    this->price = price;
    this->numberOfAvailable = 10;
}

string Album::albumDetails()
{
    std::stringstream out;

    out<<this->id<<" "<<this->albumName<<" "<<this->singerName<<" "<<this->price<<"\n";

    for(int i=0;i<tracks.size();i++)
    {
        Track temp = tracks.at(i);
        out<<"\t"<<temp.trackDetails()<<"\n";
    }

    return out.str();
}

void Album::addNewTrack(int index, string name, double duration, double price)
{
    Track newTrack(this->id,index,name,duration,price);
    tracks.push_back(newTrack);
}

string Album::albumStatus()
{
    std::stringstream out;
    out << this->id<<" "<<this->albumName<<" "<<status()<<"\n";
    return out.str();
}

int Album::getAlbumID()
{
    return this->id;
}

void Album::increase(int value)
{
    this->numberOfAvailable = this->numberOfAvailable + value;
}

string Album::status()
{
    string out;

    if(this->numberOfAvailable > 0)
        out = "Available";
    else
        out = "Sold Out";

    return out;
}
