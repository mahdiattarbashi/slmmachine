#include "buddymanager.h"

buddyManager::buddyManager()
{
}

void buddyManager::loadBuddiesAndIPs()
{
    int i;// loop variable

    //clear the lists
    AliasBuddyList.clear();
    IPBuddyList.clear();

    //begin a group called Buddies to get contact list preferences
    persistentBuddyData.beginGroup("Buddies");

    //fill the Buddy list and resize the IP buddy List
    AliasBuddyList = persistentBuddyData.allKeys();
    IPBuddyList = persistentBuddyData.allKeys();

    //fill the IP List with IPs
    for(i=0;i<AliasBuddyList.size();i++)
    {
        IPBuddyList[i] = persistentBuddyData.value(AliasBuddyList[i]).toString();
    }
    //close the group
    persistentBuddyData.endGroup();

    //get the encryption key if it is set, otherwise use default key
    if(!persistentBuddyData.value("Encryption/EncryptionKey").toString().isEmpty())
    {
        this->setKey(persistentBuddyData.value("Encryption/EncryptionKey").toString());
    }
    else
    {
        this->setKey("qazwsxedcSMG");
    }
}

void buddyManager::storeBuddies()
{
    int i;//loop variable

    //clear the QSettings Object
    persistentBuddyData.clear();

    //begin a group called Buddies to store contact list preferences
    persistentBuddyData.beginGroup("Buddies");

    //write buddy aliases and corresponding IP Addresses
    for(i=0;i<AliasBuddyList.size();i++)
    {
        persistentBuddyData.setValue(AliasBuddyList[i], IPBuddyList[i]);
    }
    //close the group
    persistentBuddyData.endGroup();

    //store the encryption key
    persistentBuddyData.setValue("Encryption/EncryptionKey", this->key);

    //write information tho the disk
    persistentBuddyData.sync();
}

//Key getter
QString buddyManager::getKey()
{
    return this->key;
}

//Key setter
void buddyManager::setKey(QString encryptionKey)
{
    this->key = encryptionKey;
}

buddyManager::~buddyManager()
{
}
