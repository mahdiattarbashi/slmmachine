#include <QtGui/QApplication>
#include <qtextcodec.h>
#include "slm_machine.h"

int main(int argc, char *argv[])
{
    //Application Information for QSettings Object to store the application data
    QCoreApplication::setOrganizationName("Guru");
    QCoreApplication::setApplicationName("SLM");

    //Apply utf8 text codecs for the application (support for Turkish Characters)
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));

    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    //TODO
    //Write Style Sheet Code

    //main user interface class
    slm_machine w;

    //disable maximize button
    w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint);

    //start the user Interface
    w.show();

    //enter application loop
    return a.exec();
}
