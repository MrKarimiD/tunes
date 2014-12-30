#include "purchase.h"

purchase::purchase()
{
}

purchase::purchase(int album_id, int track_id)
{
    this->album_id = album_id;
    this->track_id = track_id;
    this->status = "ok";
}

string purchase::show()
{
    std::stringstream out;
    out<<this->album_id<<"\t"<<this->track_id;
    return out.str();
}

int purchase::get_album_id()
{
    return this->album_id;
}

int purchase::get_track_id()
{
    return this->track_id;
}

void purchase::set_status(string status)
{
    this->status = status;
}

string purchase::get_status()
{
    return this->status;
}
