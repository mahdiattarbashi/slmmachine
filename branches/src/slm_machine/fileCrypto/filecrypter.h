#ifndef FILECRYPTER_H
#define FILECRYPTER_H

#include <QObject>
#include <QString>
#include <QMessageBox>

class fileCrypter : public QObject
{
    Q_OBJECT
public:
    fileCrypter();
    void startEnc(QString,QString);
    void startDec(QString,QString);

private:
    void algo1e(QString, QString);
    void algo1d(QString, QString);
};

#endif // FILECRYPTER_H
