/********************************************************************************
** Form generated from reading ui file 'aboutQT.ui'
**
** Created: Mon 16. Feb 08:47:33 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ABOUTQT_H
#define UI_ABOUTQT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_aboutQTDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *aboutQT_OKButton;

    void setupUi(QDialog *aboutQTDialog)
    {
    if (aboutQTDialog->objectName().isEmpty())
        aboutQTDialog->setObjectName(QString::fromUtf8("aboutQTDialog"));
    aboutQTDialog->setWindowModality(Qt::ApplicationModal);
    aboutQTDialog->resize(468, 340);
    verticalLayout = new QVBoxLayout(aboutQTDialog);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    textEdit = new QTextEdit(aboutQTDialog);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    QFont font;
    font.setFamily(QString::fromUtf8("Arial"));
    font.setBold(false);
    font.setWeight(50);
    font.setKerning(true);
    font.setStyleStrategy(QFont::PreferAntialias);
    textEdit->setFont(font);
    textEdit->setAutoFillBackground(true);
    textEdit->setReadOnly(true);

    verticalLayout->addWidget(textEdit);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    aboutQT_OKButton = new QPushButton(aboutQTDialog);
    aboutQT_OKButton->setObjectName(QString::fromUtf8("aboutQT_OKButton"));
    QFont font1;
    font1.setFamily(QString::fromUtf8("Arial"));
    aboutQT_OKButton->setFont(font1);

    horizontalLayout->addWidget(aboutQT_OKButton);


    verticalLayout->addLayout(horizontalLayout);


    retranslateUi(aboutQTDialog);

    QMetaObject::connectSlotsByName(aboutQTDialog);
    } // setupUi

    void retranslateUi(QDialog *aboutQTDialog)
    {
    aboutQTDialog->setWindowTitle(QApplication::translate("aboutQTDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    textEdit->setHtml(QApplication::translate("aboutQTDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt; font-weight:600;\">About Qt</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Helvetica'; font-size:9pt; font-weight:600;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt;\">This program uses Qt Open Source Edition version 4.5.0-rc1.</span></p>\n"
"<p sty"
        "le=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt;\">Qt Open Source Edition is intended for the development of Open Source applications. You need a commercial Qt license for development of proprietary (closed source) applications.</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt;\">Please see </span><a href=\"http://qtsoftware.com/company/model/\"><span style=\" font-family:'Helvetica'; font-size:9pt; text-decoration: underline; color:#0000ff;\">qtsoftware.com/company/model/</span></a><span style=\" font-family:'Helvetica'; font-size:9pt;\"> for an overview of Qt licensing.</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; fo"
        "nt-size:9pt;\">Qt is a C++ toolkit for cross-platform application development.</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt;\">Qt provides single-source portability across MS\302\240Windows, Mac\302\240OS\302\240X, Linux, and all major commercial Unix variants. Qt is also available for embedded devices as Qt for Embedded Linux and Qt for Windows CE.</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt;\">Qt is a Nokia product. See </span><a href=\"http://qtsoftware.com/qt/\"><span style=\" font-family:'Helvetica'; font-size:9pt; text-decoration: underline; color:#0000ff;\">qtsoftware.com/qt/</span></a><span style=\" font-family:'Helvetica'; font-size:9pt;\"> for more information.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    aboutQT_OKButton->setText(QApplication::translate("aboutQTDialog", "OK", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(aboutQTDialog);
    } // retranslateUi

};

namespace Ui {
    class aboutQTDialog: public Ui_aboutQTDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTQT_H
