#include "securestring.h"

securestring::securestring()
{
}

//TODO
//Use more intelligent encryption and decryption method
QString securestring::dencrypt(QString data, QString encryptionKey)
{
    int x, y, t;
    char a, b;
    QByteArray u, v, m;
    u = data.toUtf8();
    v = encryptionKey.toUtf8();
    t = v.size() - 1;
    y = 0;

    u = this->eliminateSpecialTurkishCharacters(u);

    for(x = 0; x < data.size(); x++)
    {
        a = (u[x] & 0x0f) ^ (v[y] & 0x0f);
        b = (u[x] & 0xf0) + a;
        u[x] = b;
        y++;
        if (y > t)
        {
            y = 0;
        }
    }
    return QString(u);
}

QByteArray securestring::eliminateSpecialTurkishCharacters(QByteArray turkishString)
{
    turkishString.replace("�","i");
    turkishString.replace("�","I");
    turkishString.replace("�","o");
    turkishString.replace("�","O");
    turkishString.replace("�","g");
    turkishString.replace("�","G");
    turkishString.replace("�","s");
    turkishString.replace("�","S");
    turkishString.replace("�","u");
    turkishString.replace("�","U");
    turkishString.replace("�","c");
    turkishString.replace("�","C");

    return turkishString;
}
