#ifndef CALIBRATIONHEAD_H
#define CALIBRATIONHEAD_H

#include <QObject>
#include <QDialog>
#include <qpoint.h>
#include <qpainter.h>
#include <qtimer.h>
#include <qelapsedtimer.h>
#include <qdebug.h>
#include "EyeTracker.h"
#include <QDesktopWidget>
#include <QRect>
#include <QApplication>

/**
 * @brief CalibrationHead class, which initiates an QDialog object with one point
 * calibration at the center. Head calibration calibrates the user's POG at 4
 * different head positions - left (idx = 1), right (idx = 2), up (idx = 3) and down (idx = 4) in order.
 */
class CalibrationHead : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief constructor for HEAD calibration objector
     *
     * @param tracker eye gaze tracker that is running
     */
    explicit CalibrationHead(EyeTracker &tracker);

    /**
     * @brief
     *
     */
    ~CalibrationHead();

    /**
     * @brief start Head calibration
     *
     * @param headIdx current index of head position
     */
    virtual void startCalibration(int headIdx);

    /**
      * @brief Sets the monitor to display head claibration
      *
      * @param monitorId monitor ID index
      */
    virtual void setMonitor(int monitorId);
signals:
    void recalibration_finished();
protected:
    int		SMALL_RADIUS; // the smallest radius that the calibration circle shrinks in px
    int		LARGE_RADIUS; // the largest radius that the calibration circle grows
    float	SHRINK_RATE; // pixels per millisecond
    float	GROW_RATE; // pixels per millisecond
    float	MOVE_RATE; // pixels per millisecond
    int		TIME_CALIBRATE; // length of data collection period in ms
    int     TIME_BUFFER; // buffer time in the beginning so that the user can fixate at
                        // the cicle, in ms

    /**
     * @brief paint even for drawing the circles
     *
     * @param default function call from Qt
     */
    virtual void paintEvent(QPaintEvent *);

    /**
     * @brief initialize calibration variables
     *
     * @param small_radius  the smallest radius that the calibration circle shrinks
     * @param large_radius  the largest radius that the calibration circle grows
     * @param shrink_rate   pixels per millisecond
     * @param grow_rate     pixels per millisecond
     * @param move_rate     pixels per millisecond
     * @param time_calibrate   length of data collection period in ms
     */
    virtual void initCalibration(int small_radius,
                         int large_radius,
                         float shrink_rate,
                         float grow_rate,
                         float move_rate,
                         int time_calibrate);

    EyeTracker*            mTracker; // eye gaze tracker that is running
    QPointF                 targetPosition; // gaze calibration position, at the center
    QElapsedTimer			elapsedTimer; // an elasped timer to keep track of time
    QTimer*					timer; // a timer to start clibration once calibration button has been clicked
    QPointF                 currPosition; // current position of calibration circle
    Qt::GlobalColor         currColor; // current color of calibration circle
    float                   currRadius; // current radius of calibration circle
    int                     headIndex; // current index of Head calibration sequence

signals:
    void finished();

private slots:
    /**
     * @brief calibration, connected to timer "timeOut" signal
     *
     */
    virtual void calibration();

    /**
     * @brief finishCalibration and call finalizeCalibration to pass the calibration target to
     * eye gaze tracker, and tracker will process the data. Connected to "finished" signal
     *
     */
    virtual void finishCalibration();
};

#endif // CALIBRATIONHEAD_H


