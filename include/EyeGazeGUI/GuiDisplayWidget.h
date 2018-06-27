#ifndef GAZEDISPLAYWIDGET_H
#define GAZEDISPLAYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <opencv2/core.hpp>


class GazeDisplayWidget : public QWidget 
{
	Q_OBJECT

public:
	GazeDisplayWidget(QWidget *parent);
	~GazeDisplayWidget();
	void drawImage(QImage image);

public Q_SLOTS:

	void paintEvent(QPaintEvent *);

private:
	QImage displayImage;
};

#endif // GazeDisplayWidget_H
