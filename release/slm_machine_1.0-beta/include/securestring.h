#ifndef SECURESTRING_H
#define SECURESTRING_H
#include <QString>
#include <QByteArray>
class securestring
{
public:
    securestring();
    QString dataIn;
    QString key;
    QString dencrypt(QString, QString);

private:
    QByteArray eliminateSpecialTurkishCharacters(QByteArray);
};

#endif // SECURESTRING_H
