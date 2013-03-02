#ifndef TESTTIMERSIGMAPPER_H
#define TESTTIMERSIGMAPPER_H

#include <QMainWindow>
#include <QTimer>
#include <QSignalMapper>

namespace Ui {
class TestTimerSigMapper;
}

class TestTimerSigMapper : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TestTimerSigMapper(QWidget *parent = 0);
    ~TestTimerSigMapper();

public Q_SLOTS:
    void print_timer_info(QString info);
    
private:
    Ui::TestTimerSigMapper *ui;
    QTimer *timer;
};

#endif // TESTTIMERSIGMAPPER_H
