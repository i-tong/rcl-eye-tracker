#include "GuiDisplayWidget.h"

GazeDisplayWidget::GazeDisplayWidget(QWidget *parent)
	: QWidget(parent)
{
	this->setMinimumWidth(640);
	this->setMinimumHeight(480);

}

GazeDisplayWidget::~GazeDisplayWidget()
{

}

void GazeDisplayWidget::drawImage(QImage image) {
	displayImage = image.copy();
	this->repaint();
}

void GazeDisplayWidget::paintEvent(QPaintEvent *) {
	QPainter p(this);
 	//p.fillRect(0,0,640,480,Qt::green);
    if (displayImage.isNull()) {
        //printf("NULL!\n");
		p.fillRect(0,0,this->width(),this->height(),Qt::gray);
	} else{
		// Determine 0,0 pixel locations
		p.fillRect(0,0,this->width(),this->height(),Qt::gray);
		int x = (this->width()-displayImage.width())/2;
		int y = (this->height()-displayImage.height())/2;
		p.drawImage(QPoint(x,y),displayImage);
	}
}
