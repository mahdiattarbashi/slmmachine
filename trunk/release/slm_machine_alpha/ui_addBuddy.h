/********************************************************************************
** Form generated from reading ui file 'addBuddy.ui'
**
** Created: Mon 16. Feb 08:43:38 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ADDBUDDY_H
#define UI_ADDBUDDY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_addBuddyScreen
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *L_buddyAliasLabel;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *L_buddyAliasLine;
    QHBoxLayout *horizontalLayout_3;
    QLabel *L_buddyIPAddressLabel;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *L_buddyIPAddressLine;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *L_addBuddyButton;
    QPushButton *L_cancelAddBuddyButton;

    void setupUi(QDialog *addBuddyScreen)
    {
    if (addBuddyScreen->objectName().isEmpty())
        addBuddyScreen->setObjectName(QString::fromUtf8("addBuddyScreen"));
    addBuddyScreen->setWindowModality(Qt::ApplicationModal);
    addBuddyScreen->resize(248, 107);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(addBuddyScreen->sizePolicy().hasHeightForWidth());
    addBuddyScreen->setSizePolicy(sizePolicy);
    QFont font;
    font.setFamily(QString::fromUtf8("Sans Serif"));
    addBuddyScreen->setFont(font);
    verticalLayout = new QVBoxLayout(addBuddyScreen);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    L_buddyAliasLabel = new QLabel(addBuddyScreen);
    L_buddyAliasLabel->setObjectName(QString::fromUtf8("L_buddyAliasLabel"));

    horizontalLayout_2->addWidget(L_buddyAliasLabel);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_2);

    L_buddyAliasLine = new QLineEdit(addBuddyScreen);
    L_buddyAliasLine->setObjectName(QString::fromUtf8("L_buddyAliasLine"));

    horizontalLayout_2->addWidget(L_buddyAliasLine);


    verticalLayout->addLayout(horizontalLayout_2);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    L_buddyIPAddressLabel = new QLabel(addBuddyScreen);
    L_buddyIPAddressLabel->setObjectName(QString::fromUtf8("L_buddyIPAddressLabel"));

    horizontalLayout_3->addWidget(L_buddyIPAddressLabel);

    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_3->addItem(horizontalSpacer_3);

    L_buddyIPAddressLine = new QLineEdit(addBuddyScreen);
    L_buddyIPAddressLine->setObjectName(QString::fromUtf8("L_buddyIPAddressLine"));

    horizontalLayout_3->addWidget(L_buddyIPAddressLine);


    verticalLayout->addLayout(horizontalLayout_3);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    L_addBuddyButton = new QPushButton(addBuddyScreen);
    L_addBuddyButton->setObjectName(QString::fromUtf8("L_addBuddyButton"));

    horizontalLayout->addWidget(L_addBuddyButton);

    L_cancelAddBuddyButton = new QPushButton(addBuddyScreen);
    L_cancelAddBuddyButton->setObjectName(QString::fromUtf8("L_cancelAddBuddyButton"));

    horizontalLayout->addWidget(L_cancelAddBuddyButton);


    verticalLayout->addLayout(horizontalLayout);


    retranslateUi(addBuddyScreen);

    QMetaObject::connectSlotsByName(addBuddyScreen);
    } // setupUi

    void retranslateUi(QDialog *addBuddyScreen)
    {
    addBuddyScreen->setWindowTitle(QApplication::translate("addBuddyScreen", "Dialog", 0, QApplication::UnicodeUTF8));
    L_buddyAliasLabel->setText(QApplication::translate("addBuddyScreen", "Alias", 0, QApplication::UnicodeUTF8));
    L_buddyIPAddressLabel->setText(QApplication::translate("addBuddyScreen", "IP Address", 0, QApplication::UnicodeUTF8));
    L_addBuddyButton->setText(QApplication::translate("addBuddyScreen", "Add", 0, QApplication::UnicodeUTF8));
    L_cancelAddBuddyButton->setText(QApplication::translate("addBuddyScreen", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(addBuddyScreen);
    } // retranslateUi

};

namespace Ui {
    class addBuddyScreen: public Ui_addBuddyScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDBUDDY_H
