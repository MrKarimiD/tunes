#include "track.h"

Track::Track()
{
}

Track::Track(int album_code, int index, string name, double duration, double price)
{
    this->album_code = album_code;
    this->index = index;
    this->name = name;
    this->duration = duration;
    this->price = price;
}

string Track::trackDetails()
{
    std::stringstream out;
    out << this->index<<" "<<this->name<<" "<<this->duration<<" "<<this->price;
    return out.str();
}

double Track::trackPrice()
{
    return this->price;
}

string Track::trackName()
{
    return this->name;
}

int Track::get_track_id()
{
    return this->index;
}
