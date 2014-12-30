#ifndef PURCHASE_LIST_H
#define PURCHASE_LIST_H

#include "purchase.h"
#include <iostream>
#include <vector>

using namespace std;

class purchase_list
{
public:
    purchase_list();
    string show_list();
    bool addPurchaseItem(purchase newItem);
    void removeItem(int album_id,int track_id);
    bool isInList(purchase item);

    vector<purchase> list;
};

#endif // PURCHASE_LIST_H
