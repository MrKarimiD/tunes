#include "album.h"

Album::Album()
{
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
