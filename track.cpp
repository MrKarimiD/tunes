#include "track.h"

Track::Track()
{
}

string Track::trackDetails()
{
    std::stringstream out;
    out << this->index<<" "<<this->name<<" "<<this->duration<<" "<<this->price;
    return out.str();
}
