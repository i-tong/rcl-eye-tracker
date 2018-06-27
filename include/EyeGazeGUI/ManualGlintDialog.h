#ifndef MANUALGLINTWINDOW_H
#define MANUALGLINTWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMouseEvent>
#include "GuiToolbar.h"
#include "GuiDisplayWidget.h"
#include "EyeTracker.h"
#include <QSettings>

class ManualGlintDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ManualGlintDialog(GazeToolbar* mainToolbar,EyeTracker* tracker, QSettings* settings,int window_size,int actual_size);
    void drawImage(QImage image);

private:
    GazeToolbar* mToolbar;
    EyeTracker* mtracker;
    QSettings* _settings;
    QImage displayImage;
    QLabel* instruction;
    QLabel* nextGlint;
    QLabel* nomenclature;
    QPushButton* nextButton;
    std::vector<QPoint> glints;//L0, L1, L2,R0,R1,R2;
    enum GLINTID {L0,L1,L2,R0,R1,R2};
    GLINTID glintid;
    float ratio;

    void setTemplate();
    std::vector<QPoint> glintmark;
//    QGroupBox* groupBox;

signals:

private slots:
    void onButtonClick();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
};

#endif // MANUALGLINTWINDOW_H
