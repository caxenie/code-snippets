/********************************************************************************
** Form generated from reading UI file 'testertimersigmapper.ui'
**
** Created: Mon Sep 3 23:22:20 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTERTIMERSIGMAPPER_H
#define UI_TESTERTIMERSIGMAPPER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TesterTimerSigMapper
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTextEdit *text_sink;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TesterTimerSigMapper)
    {
        if (TesterTimerSigMapper->objectName().isEmpty())
            TesterTimerSigMapper->setObjectName(QString::fromUtf8("TesterTimerSigMapper"));
        TesterTimerSigMapper->resize(400, 300);
        centralWidget = new QWidget(TesterTimerSigMapper);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 0, 333, 228));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        text_sink = new QTextEdit(groupBox);
        text_sink->setObjectName(QString::fromUtf8("text_sink"));

        gridLayout->addWidget(text_sink, 0, 0, 1, 1);

        TesterTimerSigMapper->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TesterTimerSigMapper);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 22));
        TesterTimerSigMapper->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TesterTimerSigMapper);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TesterTimerSigMapper->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TesterTimerSigMapper);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TesterTimerSigMapper->setStatusBar(statusBar);

        retranslateUi(TesterTimerSigMapper);

        QMetaObject::connectSlotsByName(TesterTimerSigMapper);
    } // setupUi

    void retranslateUi(QMainWindow *TesterTimerSigMapper)
    {
        TesterTimerSigMapper->setWindowTitle(QApplication::translate("TesterTimerSigMapper", "TesterTimerSigMapper", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("TesterTimerSigMapper", "TestTimerSigMapper", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TesterTimerSigMapper: public Ui_TesterTimerSigMapper {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTERTIMERSIGMAPPER_H
