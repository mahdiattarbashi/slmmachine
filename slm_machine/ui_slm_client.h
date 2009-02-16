/********************************************************************************
** Form generated from reading ui file 'slm_client.ui'
**
** Created: Mon Feb 16 22:45:10 2009
**      by: Qt User Interface Compiler version 4.5.0-rc1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SLM_CLIENT_H
#define UI_SLM_CLIENT_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_slm_clientWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *slm_clientIncomingTextArea;
    QFrame *line;
    QLineEdit *slm_client_outgoingTextArea;

    void setupUi(QMainWindow *slm_clientWindow)
    {
        if (slm_clientWindow->objectName().isEmpty())
            slm_clientWindow->setObjectName(QString::fromUtf8("slm_clientWindow"));
        slm_clientWindow->resize(403, 318);
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        slm_clientWindow->setFont(font);
        slm_clientWindow->setFocusPolicy(Qt::StrongFocus);
        centralwidget = new QWidget(slm_clientWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        slm_clientIncomingTextArea = new QTextEdit(centralwidget);
        slm_clientIncomingTextArea->setObjectName(QString::fromUtf8("slm_clientIncomingTextArea"));
        slm_clientIncomingTextArea->setFont(font);
        slm_clientIncomingTextArea->setLocale(QLocale(QLocale::Turkish, QLocale::Turkey));
        slm_clientIncomingTextArea->setReadOnly(true);

        verticalLayout->addWidget(slm_clientIncomingTextArea);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        slm_client_outgoingTextArea = new QLineEdit(centralwidget);
        slm_client_outgoingTextArea->setObjectName(QString::fromUtf8("slm_client_outgoingTextArea"));
        slm_client_outgoingTextArea->setLocale(QLocale(QLocale::Turkish, QLocale::Turkey));

        verticalLayout->addWidget(slm_client_outgoingTextArea);

        slm_clientWindow->setCentralWidget(centralwidget);
        QWidget::setTabOrder(slm_client_outgoingTextArea, slm_clientIncomingTextArea);

        retranslateUi(slm_clientWindow);

        QMetaObject::connectSlotsByName(slm_clientWindow);
    } // setupUi

    void retranslateUi(QMainWindow *slm_clientWindow)
    {
        slm_clientWindow->setWindowTitle(QApplication::translate("slm_clientWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(slm_clientWindow);
    } // retranslateUi

};

namespace Ui {
    class slm_clientWindow: public Ui_slm_clientWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLM_CLIENT_H
