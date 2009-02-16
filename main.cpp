#include <QtGui/QApplication>
#include "slm_machine.h"
#include <qtextcodec.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Guru");
    QCoreApplication::setApplicationName("SLM");

    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));

    QApplication a(argc, argv);
    slm_machine w;
    w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint); //disable maximize button
    w.show();
    return a.exec();
}
