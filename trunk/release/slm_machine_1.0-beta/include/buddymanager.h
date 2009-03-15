#ifndef BUDDYMANAGER_H
#define BUDDYMANAGER_H

#include <QObject>
#include <QSettings>
#include <QStringList>

class buddyManager : public QObject
{
public:
    buddyManager();
    ~buddyManager();

    void loadBuddiesAndIPs();
    void storeBuddies();
    QString getKey();
    void setKey(QString);

    QStringList AliasBuddyList;
    QStringList IPBuddyList;

    QSettings persistentBuddyData;
private:
    QString key;

};

#endif // BUDDYMANAGER_H
