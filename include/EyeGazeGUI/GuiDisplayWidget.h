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
