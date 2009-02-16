#include "buddymanager.h"

buddyManager::buddyManager()
{
    persistentBuddyData.setDefaultFormat(QSettings::IniFormat);
}

void buddyManager::loadBuddiesAndIPs()
{
    int i;

    AliasBuddyList.clear();
    IPBuddyList.clear();

    AliasBuddyList = persistentBuddyData.allKeys();
    IPBuddyList = persistentBuddyData.allKeys();

    for(i=0;i<AliasBuddyList.size();i++)
    {
        IPBuddyList[i] = persistentBuddyData.value(AliasBuddyList[i]).toString();
    }
}

void buddyManager::storeBuddies()
{
    int i;

    persistentBuddyData.clear();

    for(i=0;i<AliasBuddyList.size();i++)
    {
        persistentBuddyData.setValue(AliasBuddyList[i], IPBuddyList[i]);
    }

    persistentBuddyData.sync();
}

buddyManager::~buddyManager()
{
}
