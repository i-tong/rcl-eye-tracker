/*
Copyright 2018 University of British Columbia (UBC), All Rights Reserved.

--- begin LGPLv3 license - do not edit ---

    This file is part of GazeTrackGUI.

    GazeTrackGUI is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

--- end LGPLv3 license
*/
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
