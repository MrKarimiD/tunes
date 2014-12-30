#include "album_db.h"

album_db::album_db()
{
}

bool album_db::loadFromText(string file_name)
{
    ifstream textFile;
    textFile.open(file_name.data());

    albums.clear();

    if (textFile.is_open())
    {
        string line;
        while ( getline(textFile,line) )
        {
            std::istringstream buf(line);
            std::istream_iterator<string> beg(buf), end;
            vector<string> tokens(beg, end);

            if(line.at(0) == '\t')
            {
                Album last = albums.at(albums.size()-1);
                string id = tokens.at(0) , duration = tokens.at(2) , price = tokens.at(3);
                last.addNewTrack(atoi(id.c_str()),tokens.at(1),atof(duration.c_str()),atof(price.c_str()));
                albums.pop_back();
                albums.push_back(last);
            }
            else
            {
                string id = tokens.at(0) , price = tokens.at(3);
                Album newOne(atoi(id.c_str()),tokens.at(1),tokens.at(2),atof(price.c_str()));
                albums.push_back(newOne);
            }

        }

        textFile.close();
        return true;
    }

    textFile.close();
    return false;
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
    Album temp(id,album_name,singer,price);
    albums.push_back(temp);

}

void album_db::addNewTrack(int album_id, int track_num, string name, double duration, double price)
{
    int index = findAlbum(album_id);

    Album &temp = albums[index];
    temp.addNewTrack(track_num,name,duration,price);
}

void album_db::increaseEntity(int album_code, int number)
{
    int index = findAlbum(album_code);

    Album &temp = albums[index];
    temp.increase(number);
}

string album_db::showAlbums()
{
    std::stringstream out;
    for(int i=0;i<albums.size();i++)
    {
        Album temp = albums.at(i);
        out<<temp.albumStatus();
    }

    return out.str();
}

string album_db::showAlbumDetails(int album_id)
{
    std::stringstream out;

    int index = findAlbum(album_id);

    Album temp = albums.at(index);
    out << temp.albumDetails();

    return out.str();
}

bool album_db::isAvailable(int album_id)
{
    int index = findAlbum(album_id);

    Album temp = albums.at(index);

    if( temp.isAvailable() )
        return true;
    return false;
}

void album_db::buyAlbum(int album_id)
{
    int index = findAlbum(album_id);

    Album &temp = albums[index];

    temp.buy();
}

void album_db::buyTrack(int album_id, int track_id)
{
    int index = findAlbum(album_id);
}

string album_db::findAlbumInfo(int album_id)
{
    string name;
    double price;
    for(int i=0;i<albums.size();i++)
    {
        Album temp = albums.at(i);
        if( temp.getAlbumID() == album_id )
        {
            name = temp.getAlbumName();
            price = temp.getAlbumPrice();
            break;
        }
    }
    std::ostringstream s;
    s << "Album\t" << name << "\t" << price;
    return s.str();
}

double album_db::findAlbumPrice(int album_id)
{
    for(int i=0;i<albums.size();i++)
    {
        Album temp = albums.at(i);
        if( temp.getAlbumID() == album_id )
            return temp.getAlbumPrice();
    }
}

string album_db::findTrackInfo(int album_id, int track_id)
{
    int index = findAlbum(album_id);
    Album temp = albums.at(index);
    return temp.findTrackInfo(track_id);
}

double album_db::findTrackPrice(int album_id, int track_id)
{
    int index = findAlbum(album_id);
    Album temp = albums.at(index);
    return temp.findTrackPrice(track_id);
}

string album_db::exportFactor(purchase_list purchaseList)
{
    std::ostringstream factor;
    double cost = 0;

    for(int i=0;i<purchaseList.list.size();i++)
    {
        purchase item;
        item = purchaseList.list.at(i);

        if(isAvailable(item.get_album_id()))
        {
            if(item.get_track_id() == 0)
            {
                factor << findAlbumInfo(item.get_album_id())<<"\n";
                cost = cost + findAlbumPrice(item.get_album_id());
            }
            else
            {
                factor << findTrackInfo(item.get_album_id(),item.get_track_id())<<"\n";
                cost = cost + findTrackPrice(item.get_album_id(),item.get_track_id());
            }
        }
        else
        {
            if(item.get_track_id() == 0)
            {
                factor << findAlbumInfo(item.get_album_id())<<"\tPending\n";
            }
            else
            {
                factor << findTrackInfo(item.get_album_id(),item.get_track_id())<<"\tPending\n";
            }
        }
    }
    factor <<"\nTotal Price : "<<cost << "\n";
    return factor.str();
}

string album_db::buyAndExportFactor(purchase_list &purchaseList, purchase_list &history)
{
    std::ostringstream factor;
    double cost = 0;

    int i =0;
    while(i<purchaseList.list.size())
    {
        purchase item;
        item = purchaseList.list.at(i);

        if(isAvailable(item.get_album_id()))
        {
            if(item.get_track_id() == 0)
            {
                buyAlbum(item.get_album_id());
                factor << findAlbumInfo(item.get_album_id())<<"\n";
                cost = cost + findAlbumPrice(item.get_album_id());
            }
            else
            {
                buyTrack(item.get_album_id(),item.get_track_id());
                factor << findTrackInfo(item.get_album_id(),item.get_track_id())<<"\n";
                cost = cost + findTrackPrice(item.get_album_id(),item.get_track_id());
            }
            purchaseList.list.erase(purchaseList.list.begin()+i);
            history.list.push_back(item);
        }
        else
        {
            purchase *tmp = &purchaseList.list.at(i);
            tmp->set_status("pending");
            i++;
        }
    }
    factor <<"\nTotal Price : "<<cost << "\n";
    return factor.str();
}

string album_db::finAlbumName(int id)
{
    string name;
    for(int i=0;i<albums.size();i++)
    {
        Album temp = albums.at(i);
        if( temp.getAlbumID() == id )
        {
            name = temp.getAlbumName();
            break;
        }
    }
    return name;
}

int album_db::findAlbum(int album_id)
{
    for(int i=0;i<albums.size();i++)
    {
        Album temp = albums.at(i);
        if( temp.getAlbumID() == album_id )
            return i;
    }
}
