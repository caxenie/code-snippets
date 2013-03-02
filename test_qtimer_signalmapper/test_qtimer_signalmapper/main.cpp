#include <QtGui/QApplication>
#include "testertimersigmapper.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  TesterTimerSigMapper w;
  w.show();
  
  return a.exec();
}
