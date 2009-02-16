/********************************************************************************
** Form generated from reading ui file 'aboutSLM.ui'
**
** Created: Mon 16. Feb 08:49:19 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ABOUTSLM_H
#define UI_ABOUTSLM_H

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

class Ui_aboutSLMDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *aboutSLM_OKButton;

    void setupUi(QDialog *aboutSLMDialog)
    {
    if (aboutSLMDialog->objectName().isEmpty())
        aboutSLMDialog->setObjectName(QString::fromUtf8("aboutSLMDialog"));
    aboutSLMDialog->resize(274, 244);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(aboutSLMDialog->sizePolicy().hasHeightForWidth());
    aboutSLMDialog->setSizePolicy(sizePolicy);
    QFont font;
    font.setFamily(QString::fromUtf8("Arial"));
    aboutSLMDialog->setFont(font);
    verticalLayout = new QVBoxLayout(aboutSLMDialog);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    textEdit = new QTextEdit(aboutSLMDialog);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    textEdit->setFont(font);
    textEdit->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

    verticalLayout->addWidget(textEdit);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    aboutSLM_OKButton = new QPushButton(aboutSLMDialog);
    aboutSLM_OKButton->setObjectName(QString::fromUtf8("aboutSLM_OKButton"));
    sizePolicy.setHeightForWidth(aboutSLM_OKButton->sizePolicy().hasHeightForWidth());
    aboutSLM_OKButton->setSizePolicy(sizePolicy);
    QFont font1;
    font1.setFamily(QString::fromUtf8("FreeSans"));
    font1.setStyleStrategy(QFont::PreferAntialias);
    aboutSLM_OKButton->setFont(font1);

    horizontalLayout->addWidget(aboutSLM_OKButton);


    verticalLayout->addLayout(horizontalLayout);


    retranslateUi(aboutSLMDialog);

    QMetaObject::connectSlotsByName(aboutSLMDialog);
    } // setupUi

    void retranslateUi(QDialog *aboutSLMDialog)
    {
    aboutSLMDialog->setWindowTitle(QApplication::translate("aboutSLMDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    textEdit->setHtml(QApplication::translate("aboutSLMDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:12pt; font-weight:600;\">About SLM</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Helvetica'; font-size:9pt;\"></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt; font-weight:600;\">SMG LAN MESSENGER</span></p>\n"
"<p style=\"-"
        "qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Helvetica'; font-size:9pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt;\">SLM stands for SMG LAN Messenger developed for hobby purposes only. </span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Helvetica'; font-size:9pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt;\">This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at"
        " your option) any later version.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Helvetica'; font-size:9pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt;\">This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Helvetica'; font-size:9pt;\"></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-fa"
        "mily:'Helvetica'; font-size:10pt; font-weight:600;\">Developer</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt; font-style:italic;\">Ahmet KURUK\303\226SE (ahmetkurukose@yahoo.com)</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Helvetica'; font-size:9pt;\"></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:10pt; font-weight:600;\">Consultants</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt; font-style:italic;\">Umut DEN\304\260Z</sp"
        "an></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt; font-style:italic;\">Fatih AKSEL</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt; font-style:italic;\">Cengiz YILMAZ</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    aboutSLM_OKButton->setText(QApplication::translate("aboutSLMDialog", "OK", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(aboutSLMDialog);
    } // retranslateUi

};

namespace Ui {
    class aboutSLMDialog: public Ui_aboutSLMDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTSLM_H
