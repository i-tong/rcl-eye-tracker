#include "CalibrationDialog.h"

CalibrationDialog::CalibrationDialog()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(changeTarget()));


    // Setup background colour
    this->setAutoFillBackground(true);
    QPalette pal = this->palette();
    int intensity = 150;
    pal.setColor(this->backgroundRole(),QColor(intensity,intensity,intensity,255));
    this->setPalette(pal);
    this->resize(640,480);

    this->setWindowFlags(Qt::FramelessWindowHint|/*Qt::WindowStaysOnTopHint|*/Qt::X11BypassWindowManagerHint);
    this->setWindowState(Qt::WindowFullScreen);



}


CalibrationDialog::~CalibrationDialog(void)
{
    delete timer;
    pTracker = NULL;
    delete pTracker;
}

void CalibrationDialog::initCalibration(int numberOfTargets,int small_radius, int large_radius, float shrink_rate, float grow_rate,
                                        float move_rate, int time_hold, int time_calibrate,rclgaze::eyeSide side, EyeTracker &tracker ) {

    sideToCalibrate = side;
    pTracker = &tracker;

    //disconnect(pTracker,SIGNAL(streamData(float,long long,cv::Point2f,cv::Point2f,bool,bool,bool,bool,cv::Point2f,bool,cv::RotatedRect,cv::RotatedRect)), \
            this,SLOT(readGazeData(float,long long,cv::Point2f,cv::Point2f,bool,bool,bool,bool,cv::Point2f,bool,cv::RotatedRect,cv::RotatedRect)));
    leftPOG = cv::Point2f(-10,-10);
    rightPOG = cv::Point2f(-10,-10);
    bestPOG = cv::Point2f(-10,-10);
    // Set calibration parameters
    _small_radius = small_radius;
    _large_radius = large_radius;
    _shrink_rate = shrink_rate;
    _grow_rate = grow_rate;
    _move_rate = move_rate;
    _time_calibrate = time_calibrate;
    _time_hold = time_hold;
    // Currently only allowed to have 5,9, or 16 targets
    currTarget = 0;
    numTargets = numberOfTargets;
    state = STOP;
    currRadius = _large_radius;

    this->setNumTargets(numberOfTargets);

    currPosition.setX(this->width() * 0.5 );
    currPosition.setY(this->height() * 0.5 );

    // Specify current direction
    QPointF desPos = targetPosition.at(currTarget);
    desPos.setX(this->width() * ( (float)desPos.x() / 100.0 ));
    desPos.setY(this->height() * ( (float)desPos.y() / 100.0 ));
    findVecDirection(currPosition, desPos, currDirection);

}

void CalibrationDialog::startCalibration() {
    //pTracker->initCalibration(targetPosition.size(), sideToCalibrate);

    currTarget = 0;
    state = START;
    currRadius = _large_radius;
    currPosition.setX(this->width() * 0.5 );
    currPosition.setY(this->height() * 0.5 );

    QPointF desPos = targetPosition.at(currTarget);
    desPos.setX(this->width() * ( (float)desPos.x() / 100.0 ));
    desPos.setY(this->height() * ( (float)desPos.y() / 100.0 ));
    findVecDirection(currPosition, desPos, currDirection);

    timer->start(30);
    elapsedTimer.start();
    holdTimeStart = elapsedTimer.elapsed();

}

void CalibrationDialog::stopCalibration() {
    state = STOP;

}

void CalibrationDialog::changeTarget() { // called for timer timeout
    int ms = elapsedTimer.elapsed();

    switch (state) {
    case (START):
        // Wait for 1.5 second
        if (ms - holdTimeStart > _time_hold) {
            state = MOVE;
        }
        break;
    case (HOLD):
        this->holdTarget(ms, 1000);
        break;
    case (SHRINK):
        this->shrinkTarget(ms);
        break;
    case (GROW):
        this->growTarget(ms);
        break;
    case (MOVE):
        this->moveTarget(ms);
        break;
    case (CALIBRATE):
        this->calibrateTarget(ms);
        break;
    case (FIN):
        break;
    case (STOP):
        break;
    }
    repaint();
    if (state != CALIBRATE && state != STOP && state != START && state != HOLD) {
        elapsedTimer.restart();
    }
}

void CalibrationDialog::holdTarget(int elapsedms, int holdTime) {
    if (elapsedms - holdTimeStart > holdTime) {
        currColor = Qt::red;
        state = SHRINK;
    }

}

void CalibrationDialog::moveTarget(int elapsedms) {

    QPointF desPos = targetPosition.at(currTarget);
    int ms = elapsedTimer.elapsed();
    desPos.setX(this->width() * ( (float)desPos.x() / 100.0 ));
    desPos.setY(this->height() * ( (float)desPos.y() / 100.0 ));

    QPointF diff = desPos - currPosition;
    float D = diff.manhattanLength();
    float d = _move_rate * float(elapsedms);
    //qDebug() << desPos.x() << desPos.y() << d<<D << (float)diff.x() * (d/D);//<< elapsedms << "*" << _move_rate;
    QPointF newDirection;
    findVecDirection(currPosition, desPos, newDirection);
    if ( abs(D) > 10 && newDirection == currDirection) { // TODO: Stop target from overshooting
        int newx = currPosition.x() + (float)diff.x() * (d/D);
        int newy = currPosition.y() + (float)diff.y() * (d/D);
        currPosition.setX(newx);
        currPosition.setY(newy);

    } else {

        currPosition.setX(desPos.x());
        currPosition.setY(desPos.y());

        // Change state
        holdTimeStart = elapsedTimer.elapsed();
        state = HOLD;
    }
}

void CalibrationDialog::growTarget(int elapsedms) {
    if ( currRadius < _large_radius ) {

        currRadius += _grow_rate * elapsedms;
    } else {
        currRadius = _large_radius;
        currTarget += 1;
        if (currTarget == numTargets) {
            // Calibration is finished
            state = FIN;
            pTracker->finalizeCalibration(sideToCalibrate);
            //connect(pTracker,SIGNAL(streamData(float,long long,cv::Point2f,cv::Point2f,bool,bool,bool,bool,cv::Point2f,bool,cv::RotatedRect,cv::RotatedRect)), \
            //        this,SLOT(readGazeData(float,long long,cv::Point2f,cv::Point2f,bool,bool,bool,bool,cv::Point2f,bool,cv::RotatedRect,cv::RotatedRect)));


        } else {
            // Calibration is not yet finished
            // Specify current direction

            QPointF desPos = targetPosition.at(currTarget);
            desPos.setX(this->width() * ( (float)desPos.x() / 100.0 ));
            desPos.setY(this->height() * ( (float)desPos.y() / 100.0 ));
            findVecDirection(currPosition, desPos, currDirection);

            // Change state
            state = MOVE;
        }
    }
}

void CalibrationDialog::shrinkTarget(int elapsedms) {
    // Change state
    elapsedTimer.restart();
    state = CALIBRATE;
    /*if ( currRadius > _small_radius) {
        currRadius -= _shrink_rate * elapsedms;
    } else {
        currRadius = _small_radius;

        // Change state
        elapsedTimer.restart();
        state = CALIBRATE;
    }*/
}

void CalibrationDialog::calibrateTarget(int elapsedms) {

   pTracker->startCalibrating(currTarget, targetPosition.at(currTarget).x(),targetPosition.at(currTarget).y());

    if (currRadius > 0.5*_small_radius) {
        currRadius -= 0.01*_shrink_rate * elapsedms;
    } else {
        currRadius = 0.5*_small_radius;
    }

    if (elapsedTimer.elapsed() < _time_calibrate) {
    } else {
        pTracker->stopCalibrating();
        currColor = Qt::green;
        state = GROW;
    }
}

void CalibrationDialog::paintEvent(QPaintEvent *) {

    if (state != FIN) { // Show calibration sequence
        this->setWindowOpacity(1.0);
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
        p.drawEllipse(currPosition,(int)(_small_radius*0.5),(int)(_small_radius*0.5));
    } else { // Draw eye gaze position
        bool rok = pTracker->getPOG(rightPOG,rclgaze::RIGHT_EYE);
        bool lok = pTracker->getPOG(leftPOG, rclgaze::LEFT_EYE);
        bool bok = pTracker->getPOG(bestPOG, rclgaze::BOTH_EYES);
        /* QPalette pal = this->palette();
        pal.setColor(this->backgroundRole(),QColor(160,160,160,0));
        this->setPalette(pal);*/
        this->setWindowOpacity(0.5);
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        // Draw test background
        p.setPen(Qt::black);

        float border = this->height() / 5;
        float dx = (this->width()-2*border)/2;
        float dy = (this->height()-2*border)/2;
        int numRows = 3;
        int numCols = 3;
        for ( int i = 0 ; i < numRows ; i++ ) {
            for ( int j = 0 ; j < numCols ; j++ ) {
                QPoint newPoint(border+i*dx, border+j*dy);
                p.setBrush(Qt::white);
                p.drawEllipse(newPoint, 50, 50);
                p.setBrush(Qt::black);
                p.drawEllipse(newPoint, 2, 2);
            }
        }

        // Draw gaze point

        float pXR, pYR, pXL, pYL, pX, pY = 0;

        pXR = this->width()  * (rightPOG.x / 100.0);
        pYR = this->height() * (rightPOG.y / 100.0);
        pXL = this->width()  * (leftPOG.x / 100.0);
        pYL = this->height() * (leftPOG.y / 100.0);
        pX =  this->width()  * (bestPOG.x / 100.0);
        pY =  this->height() * (bestPOG.y / 100.0);

        /*p.setBrush(Qt::gray);
        p.setPen(Qt::NoPen);
        p.drawEllipse(QPointF(pXR,pYR),_small_radius, _small_radius);
        p.drawEllipse(QPointF(pXL,pYL),_small_radius,_small_radius);*/
        if (!isnan(pX) && !isnan(pY)) {
            p.setBrush(Qt::magenta);
            p.setPen(Qt::NoPen);
            p.drawEllipse(QPointF(pX,pY),_small_radius,_small_radius);
        }
        if (!isnan(pXR) && !isnan(pYR)) {
            p.setBrush(Qt::blue);
            p.drawEllipse(QPointF(pXR,pYR),_small_radius,_small_radius);
        }
        if (!isnan(pXL) && !isnan(pYL)) {
            p.setBrush(Qt::red);
            p.drawEllipse(QPointF(pXL,pYL),_small_radius,_small_radius);
        }
    }
}

bool CalibrationDialog::isCalibrationRunning() {
    if (state == FIN || state == STOP) {
        return false;
    } else {
        return true;
    }
}

bool CalibrationDialog::addCalibrationPoint(float calibration_point_x, float calibration_point_y)
{
    if (calibration_point_x < 0 || calibration_point_x > 100 || calibration_point_y < 0 || calibration_point_y >100) {
        return false;
    }
    else{
        // TODO: check if the same position has been added
//        for(auto& position: targetPosition) {

//        }
        targetPosition.push_back(QPointF(calibration_point_x,calibration_point_y));
        return true;
    }
}

float CalibrationDialog::getCalibrationTimeout() {
    return _time_calibrate;
}

float CalibrationDialog::getCalibrationDelay(){
    return _time_hold;
}

float CalibrationDialog::getNumTargets() {
    return targetPosition.size();
}

void CalibrationDialog::getCalibrationPoints(std::vector<cv::Point2f>& pos) {
    pos.clear();
    for (unsigned int i = 0 ; i < targetPosition.size() ; i++) {
        pos.push_back(cv::Point2f(targetPosition.at(i).x(),targetPosition.at(i).y()));
    }
}

void CalibrationDialog::setNumTargets(int numTargets) {
    // TODO: It would be nice if the user could set custom target positions
    targetPosition.clear();
    switch (numTargets) {
    case (0):
        targetPosition.clear();
        break;
    case (5):
        targetPosition.push_back(QPointF( 20,30));
        targetPosition.push_back(QPointF( 80,30));
        targetPosition.push_back(QPointF( 50,50));
        targetPosition.push_back(QPointF( 20,70));
        targetPosition.push_back(QPointF( 80,70));
        break;

    case (9):
            targetPosition.push_back(QPointF( 20, 25));
        targetPosition.push_back(QPointF(50, 25));
            targetPosition.push_back(QPointF(80, 25));
        targetPosition.push_back(QPointF( 20,50));
              targetPosition.push_back(QPointF(50,50));
        targetPosition.push_back(QPointF(80,50));
            targetPosition.push_back(QPointF(20,75));
        targetPosition.push_back(QPointF(50,75));
            targetPosition.push_back(QPointF(80,75));
        break;
    case (16):
        targetPosition.push_back(QPointF(20,23));
        targetPosition.push_back(QPointF(40,23));
        targetPosition.push_back(QPointF(60,23));
        targetPosition.push_back(QPointF(80,23));

        targetPosition.push_back(QPointF(80,41));
        targetPosition.push_back(QPointF(60,41));
        targetPosition.push_back(QPointF(40,41));
        targetPosition.push_back(QPointF(20,41));

        targetPosition.push_back(QPointF(20,59));
        targetPosition.push_back(QPointF(40,59));
        targetPosition.push_back(QPointF(60,59));
        targetPosition.push_back(QPointF(80,59));

        targetPosition.push_back(QPointF(80,75));
        targetPosition.push_back(QPointF(60,75));
        targetPosition.push_back(QPointF(40,75));
        targetPosition.push_back(QPointF(20,75));
        break;
    default:
        break;
    }
}


void CalibrationDialog::setCalibrationTimeout(float timeout) {
    if (timeout >= 0) {
        this->_time_calibrate = timeout;
    }
}

void CalibrationDialog::setCalibrationDelay(float delay) {
    if (delay >= 0) {
        this->_time_hold = delay;
    }
}

void CalibrationDialog::setEyeSide(rclgaze::eyeSide side) {
    this->sideToCalibrate = side;
}

void CalibrationDialog::readGazeData(float time, \
                                     long long timeTick, \
                                     cv::Point2f POGLeft, \
                                     cv::Point2f POGRight, \
                                     bool pogValidLeft, \
                                     bool pogValidRight, \
                                     bool eyeFoundLeft, \
                                     bool eyeFoundRight, \
                                     cv::Point2f POGBest, \
                                     bool pogValidBest, \
                                     cv::RotatedRect pupilLeft, \
                                     cv::RotatedRect pupilRight) {
    //qDebug() << POGBest.x << POGBest.y;
    if (pogValidLeft) {
        leftPOG = POGLeft;
    } else {
        leftPOG = cv::Point(-10,10);
    }

    if (pogValidRight) {
        rightPOG = POGRight;
    } else {
        rightPOG = cv::Point(-10,10);
    }

    if (pogValidBest) {
        bestPOG = POGBest;
    } else {
        bestPOG = cv::Point(-10,10);
    }

}
