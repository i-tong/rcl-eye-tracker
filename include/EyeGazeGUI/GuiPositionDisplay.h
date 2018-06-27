#ifndef GAZEPOSITIONDISPLAY_H
#define GAZEPOSITIONDISPLAY_H

#include <QDialog>
#include <qpoint.h>
#include <qpainter.h>
#include <qtimer.h>
#include <qelapsedtimer.h>
#include "EyeTracker.h"
#include "EyeGazeCommon.h"
#include "UtilGui.h"
#include <qdebug.h>


class GazePositionDisplay : public QDialog
{
    Q_OBJECT

public:
    GazePositionDisplay(EyeTracker &tracker);
    ~GazePositionDisplay(void);
public slots:
   void update();

 private:
   void paintEvent(QPaintEvent *event);
  EyeTracker*  pTracker;
    QTimer* mtimer;
};

#endif // GAZEPOSITIONDISPLAY_H
