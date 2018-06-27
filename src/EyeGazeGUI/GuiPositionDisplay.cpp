#include "GuiPositionDisplay.h"

GazePositionDisplay::GazePositionDisplay(EyeTracker &tracker)
{
    pTracker = &tracker;
    this->setWindowState(Qt::WindowFullScreen);

    // Setup background colour
    this->setAutoFillBackground(true);
    QPalette pal = this->palette();
    pal.setColor(this->backgroundRole(),QColor(160,160,160,255));
    this->setPalette(pal);
    this->resize(640,480);

    mtimer = new QTimer(this);

    connect(mtimer, SIGNAL(timeout()), this, SLOT(update()));
    mtimer->start(30);
}

GazePositionDisplay::~GazePositionDisplay(void) {


}

void GazePositionDisplay::update() {
    repaint();

}

void GazePositionDisplay::paintEvent(QPaintEvent *event) {


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


        // Draw gazepoint
        cv::Point2f pogR;
        cv::Point2f pogL;

        bool rightEyeGood = pTracker->getPOG(pogR, rclgaze::RIGHT_EYE);
        bool leftEyeGood =  pTracker->getPOG(pogL, rclgaze::LEFT_EYE);

        float pXR, pYR, pXL, pYL, numEyes = 0;
        if (rightEyeGood) {
            pXR = this->width() * ((float)pogR.x / 100.0);
            pYR = this->height() * ((float)pogR.y / 100.0);
            numEyes += 1;
        }
        if (leftEyeGood) {
            pXL = this->width() * ((float)pogL.x / 100.0);
            pYL = this->height() * ((float)pogL.y / 100.0);
            numEyes += 1;
        }
        float pX = (pXR+pXL)/(numEyes);
        float pY = (pYR+pYL)/(numEyes);

        int SMALL_RADIUS = 10;
        /*p.setBrush(Qt::gray);
        p.setPen(Qt::NoPen);
        p.drawEllipse(QPointF(pXR,pYR),SMALL_RADIUS, SMALL_RADIUS);
        p.drawEllipse(QPointF(pXL,pYL),SMALL_RADIUS,SMALL_RADIUS);
        p.setBrush(Qt::magenta);
        p.setPen(Qt::NoPen);
        p.drawEllipse(QPointF(pX,pY),SMALL_RADIUS,SMALL_RADIUS);*/

        p.setBrush(Qt::blue);
        p.drawEllipse(QPointF(pXR,pYR),SMALL_RADIUS,SMALL_RADIUS);

        p.setBrush(Qt::red);
        p.drawEllipse(QPointF(pXL,pYL),SMALL_RADIUS,SMALL_RADIUS);

        p.drawText(QPointF(320,240),QString::number(pXR-pXL));
}

