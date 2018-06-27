#include "CalibrationHead.h"

CalibrationHead::CalibrationHead(EyeTracker &tracker) : mTracker(&tracker)
{
    this->setWindowState(Qt::WindowFullScreen);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowOpacity(0.9);
    this->move(1600,0);

    this->setAutoFillBackground(true);
    QPalette pal = this->palette();
    int intensity = 150;
    pal.setColor(this->backgroundRole(),QColor(intensity,intensity,intensity,255));
    this->setPalette(pal);
    this->resize(640,480);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(calibration()));
    connect(this,SIGNAL(finished()),this,SLOT(finishCalibration()));
    initCalibration(10,20,0.1,0.1,0.9,800);
}

CalibrationHead::~CalibrationHead(void)
{
    qDebug() << "Exitting HEAD movement calibration dialog";
    this->close();
    this->deleteLater();
}


void CalibrationHead::initCalibration(int small_radius,
                                          int large_radius,
                                          float shrink_rate,
                                          float grow_rate,
                                          float move_rate,
                                          int time_calibrate)
{
    // Set calibration parameters
    SMALL_RADIUS = small_radius;
    LARGE_RADIUS = large_radius;
    SHRINK_RATE = shrink_rate;
    GROW_RATE = grow_rate;
    MOVE_RATE = move_rate;
    TIME_CALIBRATE = time_calibrate;
    TIME_BUFFER = 1000;

    targetPosition = QPoint(50,50);
    currRadius = LARGE_RADIUS;
    currColor = Qt::red;

    QPointF desPos = targetPosition;
    desPos.setX(this->width() * ( (float)desPos.x() / 100.0 ));
    desPos.setY(this->height() * ( (float)desPos.y() / 100.0 ));
    currPosition = desPos;
    mTracker->initReCalibration();
}

void CalibrationHead::startCalibration(int index)
{
    mTracker->initReCalibration(false);
    headIndex = index;
    this->show();
    this->raise();
    timer->start(30);
    elapsedTimer.start();
}

void CalibrationHead::calibration()
{
    mTracker->startRecalibration(cv::Point2f(targetPosition.x(),targetPosition.y()));
    int elapsedms = elapsedTimer.elapsed();
    if (elapsedms > TIME_BUFFER){
        if (currRadius > 0.5*SMALL_RADIUS) {
            currRadius -= 0.01*SHRINK_RATE * (elapsedms-TIME_BUFFER);
        } else {
            currRadius = 0.5*SMALL_RADIUS;
        }
    }
    if (elapsedms > TIME_BUFFER + TIME_CALIBRATE) {
        mTracker->stopCalibrating();
        currRadius = LARGE_RADIUS;
        emit finished();
        timer->stop();
    }

    this->update();
}

void CalibrationHead::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    if (this->currColor == Qt::red) {
        p.setBrush(Qt::red);
    } else {
        p.setBrush(Qt::green);
    }
    p.setPen(Qt::NoPen);
    p.drawEllipse(currPosition,(int)currRadius,(int)currRadius);
    if (this->currColor == Qt::red) {
        p.setBrush(Qt::darkRed);
    } else {
        p.setBrush(Qt::darkGreen);
    }
    p.drawEllipse(currPosition,(int)(SMALL_RADIUS*0.5),(int)(SMALL_RADIUS*0.5));
}

void CalibrationHead::finishCalibration()
{
    this->hide();
    timer->stop();
    if (mTracker->finalizeReCalibration(cv::Point2f(targetPosition.x(),targetPosition.y())
                                        ,headIndex)){
        emit recalibration_finished();
        qDebug()<<"Session finished";
    }
    else{
        qDebug()<< "Error in this head-movement calibration";
    }
}

void CalibrationHead::setMonitor(int monitorId) {
    QDesktopWidget* deskWin = QApplication::desktop();
    QRect monitorRect = deskWin->availableGeometry(monitorId);
    this->move(QPoint(QPoint(monitorRect.x(),monitorRect.y())));

}
