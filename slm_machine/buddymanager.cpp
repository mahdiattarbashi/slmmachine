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

    persistentBuddyData.beginGroup("Buddies");

    AliasBuddyList = persistentBuddyData.allKeys();
    IPBuddyList = persistentBuddyData.allKeys();

    for(i=0;i<AliasBuddyList.size();i++)
    {
        IPBuddyList[i] = persistentBuddyData.value(AliasBuddyList[i]).toString();
    }
    persistentBuddyData.endGroup();

    if(!persistentBuddyData.value("Encryption/EncryptionKey").toString().isEmpty())
    {
        this->setKey(persistentBuddyData.value("Encryption/EncryptionKey").toString());
    }
    else
    {
        this->setKey("qweertesdjhfgjhsdfsmg2008xbnxcvbnxvashgdahgdhafdajhfdvsbdcvgsdvf");
    }
}

void buddyManager::storeBuddies()
{
    int i;

    persistentBuddyData.clear();

    persistentBuddyData.beginGroup("Buddies");

    for(i=0;i<AliasBuddyList.size();i++)
    {
        persistentBuddyData.setValue(AliasBuddyList[i], IPBuddyList[i]);
    }

    persistentBuddyData.endGroup();

    persistentBuddyData.setValue("Encryption/EncryptionKey", this->key);

    persistentBuddyData.sync();
}

QString buddyManager::getKey()
{
    return this->key;
}

void buddyManager::setKey(QString encryptionKey)
{
    this->key = encryptionKey;
}

buddyManager::~buddyManager()
{
}
