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

Album::Album(int id, string albumName, string singerName, double price, int number)
{
    this->id = id;
    this->albumName = albumName;
    this->singerName = singerName;
    this->price = price;
    this->numberOfAvailable = number;
}

string Album::albumDetails()
{
    std::stringstream out;

    out<<this->id<<" "<<this->albumName<<" "<<this->singerName<<" "<<this->price<< " " << this->number() <<"\n";

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

bool Album::isAvailable()
{
    if( this->numberOfAvailable > 0)
        return true;
    return false;
}

double Album::buy()
{
    this->numberOfAvailable--;
    return this->price;
}

string Album::getAlbumName()
{
    return this->albumName;
}

double Album::getAlbumPrice()
{
    return this->price;
}

string Album::findTrackInfo(int track_id)
{
    std::ostringstream s;
    int index = findTrack(track_id);
    Track tr = tracks.at(index);
    s << "Track\t"<<tr.trackName()<<"\t"<<tr.trackPrice();
    return s.str();
}

double Album::findTrackPrice(int track_id)
{
    int index = findTrack(track_id);
    Track tr = tracks.at(index);
    return tr.trackPrice();
}

int Album::number()
{
    return this->numberOfAvailable;
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

int Album::findTrack(int track_id)
{
    for(int i=0;i<tracks.size();i++)
    {
        Track temp = tracks.at(i);
        if( temp.get_track_id()  == track_id )
            return i;
    }
}
