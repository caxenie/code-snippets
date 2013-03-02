/********************************************************************************
** Form generated from reading UI file 'testtimersigmapper.ui'
**
** Created: Tue Sep 4 11:23:03 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTTIMERSIGMAPPER_H
#define UI_TESTTIMERSIGMAPPER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestTimerSigMapper
{
public:
    QWidget *centralWidget;
    QTextEdit *textEdit;

    void setupUi(QMainWindow *TestTimerSigMapper)
    {
        if (TestTimerSigMapper->objectName().isEmpty())
            TestTimerSigMapper->setObjectName(QString::fromUtf8("TestTimerSigMapper"));
        TestTimerSigMapper->resize(796, 634);
        centralWidget = new QWidget(TestTimerSigMapper);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 10, 771, 611));
        TestTimerSigMapper->setCentralWidget(centralWidget);

        retranslateUi(TestTimerSigMapper);

        QMetaObject::connectSlotsByName(TestTimerSigMapper);
    } // setupUi

    void retranslateUi(QMainWindow *TestTimerSigMapper)
    {
        TestTimerSigMapper->setWindowTitle(QApplication::translate("TestTimerSigMapper", "TestTimerSigMapper", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TestTimerSigMapper: public Ui_TestTimerSigMapper {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTTIMERSIGMAPPER_H
