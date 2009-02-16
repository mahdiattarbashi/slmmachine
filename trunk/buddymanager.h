#ifndef BUDDYMANAGER_H
#define BUDDYMANAGER_H

#include <QObject>
//#include <QHash>
//#include <QFile>
//#include <QFileInfo>
//#include <QTextStream>
 #include <QSettings>
#include <QStringList>

class buddyManager : public QObject
{
public:
    buddyManager();
    ~buddyManager();

    void loadBuddiesAndIPs();
    void storeBuddies();

    QStringList AliasBuddyList;
    QStringList IPBuddyList;

    //QFile AliasBuddyListFile;
    //QFile IPBuddyListFile;

    //QTextStream AliasBuddyListFileTextStream;
    //QTextStream IPBuddyListFileTextStream;


    QSettings persistentBuddyData;

};

#endif // BUDDYMANAGER_H
