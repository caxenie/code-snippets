#include "testtimersigmapper.h"
#include "ui_testtimersigmapper.h"

TestTimerSigMapper::TestTimerSigMapper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestTimerSigMapper)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    // signal mapper
    QSignalMapper *sig_map = new QSignalMapper(this);
    sig_map->setMapping(timer, QString("TIMER1"));
    connect(timer, SIGNAL(timeout()), sig_map, SLOT(map()));
    connect(sig_map, SIGNAL(mapped(QString)), this, SLOT(print_timer_info(QString)));
    timer->start(2000); // ms
}

void TestTimerSigMapper::print_timer_info(QString info)
{
    char* c_info = (char*)info.toStdString().c_str();
    ui->textEdit->append(c_info);
}

TestTimerSigMapper::~TestTimerSigMapper()
{
    delete ui;
}
