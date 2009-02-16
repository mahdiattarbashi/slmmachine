/********************************************************************************
** Form generated from reading ui file 'slm_machine.ui'
**
** Created: Mon 16. Feb 08:43:38 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SLM_MACHINE_H
#define UI_SLM_MACHINE_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_slm_machineClass
{
public:
    QAction *actionExit;
    QAction *actionAbout_Qt;
    QAction *actionAbout_SLM;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QListView *buddyList;
    QHBoxLayout *horizontalLayout;
    QPushButton *addBuddyButton;
    QPushButton *removeBuddyButton;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QMenu *menuAbout;

    void setupUi(QMainWindow *slm_machineClass)
    {
    if (slm_machineClass->objectName().isEmpty())
        slm_machineClass->setObjectName(QString::fromUtf8("slm_machineClass"));
    slm_machineClass->resize(224, 400);
    QFont font;
    font.setFamily(QString::fromUtf8("Sans Serif"));
    font.setPointSize(9);
    slm_machineClass->setFont(font);
    slm_machineClass->setLocale(QLocale(QLocale::Turkish, QLocale::Turkey));
    actionExit = new QAction(slm_machineClass);
    actionExit->setObjectName(QString::fromUtf8("actionExit"));
    actionAbout_Qt = new QAction(slm_machineClass);
    actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
    actionAbout_SLM = new QAction(slm_machineClass);
    actionAbout_SLM->setObjectName(QString::fromUtf8("actionAbout_SLM"));
    centralWidget = new QWidget(slm_machineClass);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    verticalLayout_2 = new QVBoxLayout(centralWidget);
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setMargin(11);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing(6);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    buddyList = new QListView(centralWidget);
    buddyList->setObjectName(QString::fromUtf8("buddyList"));

    verticalLayout->addWidget(buddyList);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(6);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    addBuddyButton = new QPushButton(centralWidget);
    addBuddyButton->setObjectName(QString::fromUtf8("addBuddyButton"));

    horizontalLayout->addWidget(addBuddyButton);

    removeBuddyButton = new QPushButton(centralWidget);
    removeBuddyButton->setObjectName(QString::fromUtf8("removeBuddyButton"));

    horizontalLayout->addWidget(removeBuddyButton);


    verticalLayout->addLayout(horizontalLayout);


    verticalLayout_2->addLayout(verticalLayout);

    slm_machineClass->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(slm_machineClass);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 224, 25));
    menuMenu = new QMenu(menuBar);
    menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
    menuAbout = new QMenu(menuBar);
    menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
    slm_machineClass->setMenuBar(menuBar);

    menuBar->addAction(menuMenu->menuAction());
    menuBar->addAction(menuAbout->menuAction());
    menuMenu->addAction(actionExit);
    menuAbout->addAction(actionAbout_Qt);
    menuAbout->addAction(actionAbout_SLM);

    retranslateUi(slm_machineClass);

    QMetaObject::connectSlotsByName(slm_machineClass);
    } // setupUi

    void retranslateUi(QMainWindow *slm_machineClass)
    {
    slm_machineClass->setWindowTitle(QApplication::translate("slm_machineClass", "slm_machine", 0, QApplication::UnicodeUTF8));
    actionExit->setText(QApplication::translate("slm_machineClass", "Exit", 0, QApplication::UnicodeUTF8));
    actionAbout_Qt->setText(QApplication::translate("slm_machineClass", "About Qt", 0, QApplication::UnicodeUTF8));
    actionAbout_SLM->setText(QApplication::translate("slm_machineClass", "About SLM", 0, QApplication::UnicodeUTF8));
    addBuddyButton->setText(QApplication::translate("slm_machineClass", "Add Buddy", 0, QApplication::UnicodeUTF8));
    removeBuddyButton->setText(QApplication::translate("slm_machineClass", "Remove Buddy", 0, QApplication::UnicodeUTF8));
    menuMenu->setTitle(QApplication::translate("slm_machineClass", "Menu", 0, QApplication::UnicodeUTF8));
    menuAbout->setTitle(QApplication::translate("slm_machineClass", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class slm_machineClass: public Ui_slm_machineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLM_MACHINE_H
