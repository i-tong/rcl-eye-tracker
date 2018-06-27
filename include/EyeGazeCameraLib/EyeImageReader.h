#ifndef EYEIMAGEREADER_H
#define EYEIMAGEREADER_H
#include "stdafx.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/videoio.hpp"
#include "opencv2/video.hpp"

#include "EyeGazeCommon.h"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

typedef boost::function<void(cv::Mat)> newframe_callback;

class EYEGAZECAMERA_API EyeImageReader {
public:
	EyeImageReader();
	~EyeImageReader();

	bool addVideoDevice(const char* filename, rclgaze::eyeSide side);
	bool addCameraDevice(const char* devicename, rclgaze::eyeSide side);

	void resetDevice(rclgaze::eyeSide side);

	bool setCamDistProp(cv::Mat& intrinsic_mat, std::vector<float>& distortion_mat, rclgaze::eyeSide side);

	bool start();
	bool stop();

	bool getFrame(cv::Mat& refRight, cv::Mat& refLeft);
	bool isRightEyeActive();
	bool isLeftEyeActive();
	void registerVideoCallback(newframe_callback callback_left, newframe_callback callback_right);
};


#endif
