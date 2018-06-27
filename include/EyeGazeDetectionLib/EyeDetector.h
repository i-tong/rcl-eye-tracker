#ifndef EYEDETECTOR_H
#define EYEDETECTOR_H
#include "stdafx.h"
// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "EyeGazeCommon.h"

class EYEGAZEDETECTION_API EyeDetector
{
public:
	EyeDetector(rclgaze::eyeSide side, std::string settings_directory);
	~EyeDetector();

	void init();
	bool findPupilGlintVector(cv::Mat srcFrame);

	bool getPupil(cv::RotatedRect& retPupil);
	bool getGlintList(std::vector<cv::Point2f>& retGlintList);
	float getGlintDistance(int index0, int index1);
	cv::Vec3f getGlintDistanceAll();
	cv::Point2f getPGVectorZero(float glintRef = -1, int glintIdx = 0);
	std::vector<cv::Point2f> getPGVectorAll(cv::Vec3f glintRef = cv::Vec3f(-1, -1, -1));
	rclgaze::eyeSide getEyeSide();

	void setGlintTemplate(int newDx, int newDy, int newDx_sec, int newDy_sec);
	void setEyeSide(rclgaze::eyeSide side);

private:
	rclgaze::eyeSide _side;

};

#endif
