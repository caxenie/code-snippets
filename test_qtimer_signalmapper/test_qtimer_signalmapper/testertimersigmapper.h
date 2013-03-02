#ifndef TESTERTIMERSIGMAPPER_H
#define TESTERTIMERSIGMAPPER_H

#include <QMainWindow>
#include <QTimer>
#include <QSignalMapper>

#define NUM_TIMERS 9
#define PERIOD 1000

namespace Ui {
  class TesterTimerSigMapper;
}

class TesterTimerSigMapper : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit TesterTimerSigMapper(QWidget *parent = 0);
  ~TesterTimerSigMapper();

public Q_SLOTS:
    void update_text(QString cmd);
  
private:
  Ui::TesterTimerSigMapper *ui;
  QTimer* timers[NUM_TIMERS];

};

#endif // TESTERTIMERSIGMAPPER_H
