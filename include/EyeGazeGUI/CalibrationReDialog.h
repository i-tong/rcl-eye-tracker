// TODO: deprecated

#ifndef CALIBRATIONREDIALOG_H
#define CALIBRATIONREDIALOG_H

#include <QObject>
#include <QDialog>
#include <qpoint.h>
#include <qpainter.h>
#include <qtimer.h>
#include <qelapsedtimer.h>
#include <qdebug.h>
#include "EyeTracker.h"


class CalibrationReDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CalibrationReDialog(EyeTracker &tracker);

    ~CalibrationReDialog();
    virtual void startCalibration();

protected:
    int		SMALL_RADIUS;
    int		LARGE_RADIUS;
    float	SHRINK_RATE; // pixels per millisecond
    float	GROW_RATE; // pixels per millisecond
    float	MOVE_RATE; // pixels per millisecond
    int		TIME_CALIBRATE;
    int     TIME_BUFFER;

    virtual void paintEvent(QPaintEvent *);
    virtual void initCalibration(int numberOfTargets,
                         int small_radius,
                         int large_radius,
                         float shrink_rate,
                         float grow_rate,
                         float move_rate,
                         int time_calibrate);

    EyeTracker*            mTracker;
    QPointF                 targetPosition;
    QElapsedTimer			elapsedTimer;
    QTimer*					timer;
    QPointF                 currPosition;
    Qt::GlobalColor         currColor;
    int                     numTargets;
    float                   currRadius;

signals:
    void finished();

private slots:
    virtual void calibration();
    virtual void finishCalibration();
};

#endif // CALIBRATIONREDIALOG_H
