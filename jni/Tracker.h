#ifndef _TRACKER_H_
#define _TRACKER_H_

#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <vector>


using namespace cv;

class Tracker {

private:
	std::string mFaceXml;
	std::string mEyeXml;

	float mFaceMinSize;
	float mEyeMinSize;

	CascadeClassifier mFaceClassifier;
	CascadeClassifier mEyeClassifier;

	std::vector<cv::Rect> detectFaces(Mat , Mat);

	std::vector<Rect> detectEyes(Mat , Mat , std::vector<Rect>);

public:
	Tracker(std::string faceCascade, std::string eye);

	bool init();

	void setFaceMinSize(float);

	void setEyeMinSize(float);

	void process(Mat , Mat);

};

#endif
