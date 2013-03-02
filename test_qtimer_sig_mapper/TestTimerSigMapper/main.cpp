#include <QtGui/QApplication>
#include "testtimersigmapper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestTimerSigMapper w;
    w.show();
    
    return a.exec();
}
