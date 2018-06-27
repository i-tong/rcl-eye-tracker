#ifndef ROSPUBLISHER_H
#define ROSPUBLISHER_H

#include "GazeTracker.h"
#include "Util.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QTimer>
b#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

/**
 * @brief RosPublisher class, publishes eye gaze info in format of JointState
 *
 */
class RosPublisher : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief default constructor
     *
     * @param parent
     */
    RosPublisher(QObject *parent = 0);

    /**
     * @brief
     *
     */
    ~RosPublisher();

    /**
     * @brief start eye gaze streaming
     *
     * @param m_tracker
     */
    void startGazePositionStream(GazeTracker* _tracker);

    /**
     * @brief stop eye gaze streaming
     *
     */
    void stopGazePositionStream();

protected:
    GazeTracker* _tracker; // reference to eye gaze tracker
    cv::Point2f	_pogRight; // pog of right eye
    cv::Point2f	_pogLeft; // pog of left eye
    cv::Point2f _pogAvg; // filtered avg pog of left and right eyes
    QTimer *_p_timer; // timer that continuously publish pog
    sensor_msgs::JointState _msg;
    ros::Publisher _pub; // ros publisher
    ros::NodeHandle _n; // ros node

public slots:
    /**
     * @brief publish eye gaze position
     *
     */
    void streamGazePosition();
};

#endif // ROSPUBLISHER_H
