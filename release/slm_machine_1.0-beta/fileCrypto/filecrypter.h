#ifndef FILECRYPTER_H
#define FILECRYPTER_H

#include <QObject>
#include <QString>
#include <QRunnable>

class fileCrypter : public QObject, public QRunnable
{
    Q_OBJECT
public:
    fileCrypter();
    void run();
    QString InputFile;
    QString OutputFile;
    int key;

private:
    void algo1e(QString, QString);
    void algo1d(QString, QString);
};

#endif // FILECRYPTER_H
