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

}

void album_db::increaseEntity(int album_code, int number)
{

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

    for(int i=0;i<albums.size();i++)
    {
        Album temp = albums.at(i);
        out << temp.albumDetails();
    }
    return out.str();
}
