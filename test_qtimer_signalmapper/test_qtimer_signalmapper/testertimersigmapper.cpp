#include "testertimersigmapper.h"
#include "ui_testertimersigmapper.h"



TesterTimerSigMapper::TesterTimerSigMapper(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::TesterTimerSigMapper)
{
  ui->setupUi(this);
  QString cmds[NUM_TIMERS] = {"!D30,0,0", "!D20,0,0", "!D23,0,0", "!D23,0, 45", "!D23,32,0", "!D23,12,12", "!D232,0,10", "!D23,0,20", "!D0,0,0"};
  for(int i=0;i<NUM_TIMERS;i++){
      timers[i] = new QTimer(this);
      QSignalMapper *sig_map = new QSignalMapper(this);
      sig_map->setMapping(timers[i],cmds[i]);
      connect(timers[i], SIGNAL(timeout()), sig_map, SLOT(map()));
      connect(sig_map, SIGNAL(mapped(QString)), this, SLOT(update_text(QString)));
    }

  timers[0]->start(9*PERIOD);
  timers[1]->start(18*PERIOD);
  timers[2]->start(27*PERIOD);
  timers[3]->start(36*PERIOD);
  timers[4]->start(45*PERIOD);
  timers[5]->start(54*PERIOD);
  timers[6]->start(63*PERIOD);
  timers[7]->start(72*PERIOD);
  timers[8]->start(91*PERIOD);
}

void TesterTimerSigMapper::update_text(QString cmd)
{
  this->ui->text_sink->append(cmd);
}

TesterTimerSigMapper::~TesterTimerSigMapper()
{
  delete ui;
}
