#ifndef UTILQT_H
#define UTILQT_H

#include <QPoint>
#include <QImage>
#include <QDebug>
#include <QString>
// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*!
    @brief Finds the direction vector between Qt points.
    @param point1 starting point
    @param point2 ending point
    @param ret vector from point1 to point2
*/
void findVecDirection(QPointF point1, QPointF point2, QPointF &ret);

/*!
    @brief Convert cv::Mat to Qt::Image

    @param src OpenCV image
    @param dst Qt image
*/
void cvtMat2Qimage(cv::Mat src, QImage &dst);


/*!
 * \brief displayCVMat prints out an OpenCV Mat object.
 * \param M OpenCV Mat matrix
 * \param name Name of matrix to display
 */
void displayCVMat(cv::Mat M, QString name) ;
std::vector<float> getNumberFromString(QString inStr);

#endif // UTILQT_H
