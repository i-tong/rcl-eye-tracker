#include "UtilGui.h"


void findVecDirection(QPointF point1, QPointF point2, QPointF &ret) {
    // Returns direction moving from point 1 to point 2
    // 1: positive direction
    // 0: no change
    //-1: negative direction
    QPointF diff = point2 - point1;

    // Determine x direction
    if (diff.x() > 1) {
        ret.setX(1);
    } else if (diff.x() < -1) {
        ret.setX(-1);
    } else {
        ret.setX(0);
    }

    // Determine y direction
    if (diff.y() > 1) {
        ret.setY(1);
    } else if (diff.y() < -1) {
        ret.setY(-1);
    } else {
        ret.setY(0);
    }
}


void cvtMat2Qimage(cv::Mat src, QImage &dst) {

    switch (src.type()) {
        case CV_8UC1:
            cv::cvtColor(src,src,CV_BGR2GRAY);
            break;
        case CV_8UC3:
            cv::cvtColor(src,src,CV_BGR2RGB);
            break;
    }

    dst = QImage(src.data, src.cols, src.rows, src.cols*3, QImage::Format_RGB888);

}


void displayCVMat(cv::Mat M, QString name) {
    QDebug debug = qDebug();
//    debug.noquote();
    debug << "\n" << name << ":\n";

    for (int i = 0; i < M.rows; i++) {
        QString row = "";
        for (int j = 0; j < M.cols ; j++) {
            row.append(QString::number(M.at<float>(i,j)));
            row.append(" ");

        }
        debug << row << "\n";
    }
    debug << "Depth" << M.depth() << CV_32F;

}

std::vector<float> getNumberFromString(QString inStr) {
    std::vector<float> retList;
    QRegExp rx("(\\d+)");
    QStringList strList;

    int pos = 0;
    while ((pos = rx.indexIn(inStr,pos)) != -1) {
        strList << rx.cap(1);
        retList.push_back(rx.cap(1).toFloat());
        pos += rx.matchedLength();
    }

    return retList;
}
