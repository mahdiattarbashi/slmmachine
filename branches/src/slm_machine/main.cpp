#include <QtGui/QApplication>
#include <qtextcodec.h>
#include <QFile>
#include "slm_machine.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Guru");
    QCoreApplication::setApplicationName("SLM");

    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));

    QApplication a(argc, argv);
    
    //TODO
    //Write Style Sheet Code
    
    // Style Sheet
    // QFile file(":/settings/style");
    // QString fileName = file.fileName();
    // bool opened = file.open(QFile::ReadOnly);
    // QString styleSheet = QLatin1String(file.readAll());
    // a.setStyleSheet(styleSheet);
 
    slm_machine w;
    w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint); //disable maximize button
    w.show();
    return a.exec();
}
