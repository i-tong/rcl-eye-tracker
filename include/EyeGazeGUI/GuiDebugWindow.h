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

