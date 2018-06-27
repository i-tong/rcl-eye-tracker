#include "RosPublisher.h"

RosPublisher::RosPublisher(QObject *parent) :
    QObject(parent)
{
    _p_timer = new QTimer(this);
    connect(_p_timer,SIGNAL(timeout()),this,SLOT(streamGazePosition()));

    _pub = _n.advertise<sensor_msgs::JointState>("gazePosition", 1000);
}

RosPublisher::~RosPublisher()
{
    _p_timer->stop();
    delete _p_timer;
}

void RosPublisher::startGazePositionStream(GazeTracker* tracker)
{
    qDebug() << "Start streaming";
    _tracker = tracker;

    _p_timer->start(10); //stream position at 100 Hz
}

void RosPublisher::stopGazePositionStream()
{
    qDebug() << "Stop streaming";
    _p_timer->stop();
}

void RosPublisher::streamGazePosition()
{
    bool rightgood = _tracker->getPOG(_pogRight,RIGHT_EYE);
    bool leftgood = _tracker->getPOG(_pogLeft,LEFT_EYE);
    if (rightgood && leftgood) {
    _pogAvg.x = (_pogRight.x + _pogLeft.x)/2;
    _pogAvg.y = (_pogRight.y + _pogLeft.y)/2;
    }
    else if (rightgood) {
        _pogAvg.x = _pogRight.x;
        _pogAvg.y = _pogRight.y;
    } else if (leftgood) {
        _pogAvg.x = _pogLeft.x;
        _pogAvg.y = _pogLeft.y;
    }
    if (_pogAvg.x && _pogAvg.y){
        _msg.position = {_pogAvg.x, _pogAvg.y};
        _pub.publish(_msg);
    }
}
