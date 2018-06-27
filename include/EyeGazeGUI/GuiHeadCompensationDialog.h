#ifndef HEADCOMPENSATIONDIALOG_H
#define HEADCOMPENSATIONDIALOG_H

#include <QDialog>
#include <EyeTracker.h>
#include <CalibrationHead.h>
#include <QMessageBox>

namespace Ui {
class HeadCompensationDialog;
}

enum headDirection {
    HEAD_LEFT,
    HEAD_RIGHT,
    HEAD_UP,
    HEAD_DOWN,
    HEAD_NONE
};

class HeadCompensationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HeadCompensationDialog(EyeTracker* tracker,QWidget *parent = 0);
    ~HeadCompensationDialog();
    void showEvent(QShowEvent *);
    void setDisplayMonitor(int monitorId);

private slots:
    void onButtonClick_left();
    void onButtonClick_right();
    void onButtonClick_up();
    void onButtonClick_down();
    void onButtonClick_finished();
    void finished();
private:
    Ui::HeadCompensationDialog *ui;
    EyeTracker* _tracker;
    CalibrationHead* _calHead;
    void showCalibrationError();
    headDirection _currDir;
    std::vector<int> _countDoneVector;
    int _monitorId;
};

#endif // HEADCOMPENSATIONDIALOG_H
