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
#ifndef GAZEDEBUGWINDOW_H
#define GAZEDEBUGWINDOW_H

//#include <qdialog.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <boost/thread.hpp>
//#include <QDebug>
struct imageData{
	const char* title;
	cv::Mat image;
};



class GazeDebugWindow {
public:
	static GazeDebugWindow& getInstance() {
		static GazeDebugWindow instance;
		return instance;
	}
	~GazeDebugWindow(void);
	bool showWindow(const char* windowTitle, cv::Mat image);

private:
	GazeDebugWindow(void);
	GazeDebugWindow(GazeDebugWindow const&);
	void operator=(GazeDebugWindow const&); // Copy constructor
	void run();
	bool runFlag;
	boost::thread thr;
	boost::mutex imagedata_mutex;
	std::vector<imageData> currData;
};

#endif

