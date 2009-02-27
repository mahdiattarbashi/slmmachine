#include "filecrypter.h"
#include <fstream>
#include <QDebug>
fileCrypter::fileCrypter()
{
    this->key = 0;
    this->setAutoDelete(1);
}
void fileCrypter::run()
{
    switch(key)
    {
        case 1:
                this->algo1e(InputFile, OutputFile);
                break;
        case 2:
                this->algo1d(InputFile, OutputFile);
                break;
        default:
                break;
    }
}
void fileCrypter::algo1e(QString inputFile, QString outputFile)
{
    unsigned long long count = 0;   // cryption counter
    unsigned char c; // tmp data
    int cc;
    std::ifstream I(inputFile.toAscii().constData(),
        std::ios_base::binary);
    std::ofstream O(outputFile.toAscii().constData(),
        std::ios_base::binary);
    while((cc = I.get()) >= 0) {
        c = (unsigned char)cc;
        switch(count%5) {
        case 0:
          c -= 0x12;
          O << c;
          break;
        case 1:
          c += 0x10;
          O << c;
          break;
        case 2:
          c -= 0x14;
          O << c;
          break;
        case 3:
          c += 0x18;
          O << c;
          break;
        case 4:
          c -= 0x16;
          O << c;
          break;
        }
        count++;
    }
    I.close();
    O.close();
}

void fileCrypter::algo1d(QString inputFile, QString outputFile)
{
    unsigned long long count = 0;   // cryption counter
    unsigned char c; // tmp data
    int cc;
    std::ifstream I(inputFile.toAscii().constData(), std::ios_base::binary);
    qDebug() << I.is_open();
    std::ofstream O(outputFile.toAscii().constData(), std::ios_base::binary);
    while((cc = I.get()) >= 0) {
        c = (unsigned char)cc;
        switch(count%5) {
        case 0:
          c += 0x12;
          O << c;
          break;
        case 1:
          c -= 0x10;
          O << c;
          break;
        case 2:
          c += 0x14;
          O << c;
          break;
        case 3:
          c -= 0x18;
          O << c;
          break;
        case 4:
          c += 0x16;
          O << c;
          break;
        }
        count++;
    }
    I.close();
    O.close();
}
