#include "securestring.h"

securestring::securestring()
{
}

//TODO
//Polish encryption and decryption method and remove eliminateTurkishCharacters function
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
    turkishString.replace("ı","i");
    turkishString.replace("İ","I");
    turkishString.replace("ö","o");
    turkishString.replace("Ö","O");
    turkishString.replace("ğ","g");
    turkishString.replace("Ğ","G");
    turkishString.replace("ş","s");
    turkishString.replace("Ş","S");
    turkishString.replace("ü","u");
    turkishString.replace("Ü","U");
    turkishString.replace("ç","c");
    turkishString.replace("Ç","C");

    return turkishString;
}
