/*
 * Tracker.cpp
 *
 *  Created on: Oct 28, 2014
 *      Author: centos
 */

#include "Tracker.h"

Tracker::Tracker(std::string faceCascade, std::string eye) {
	this->mFaceXml = faceCascade;
	this->mEyeXml = eye;
	this->mFaceMinSize = 200;
	this->mEyeMinSize = 30;
}

void Tracker::setEyeMinSize(int size) {
	mEyeMinSize = size;
}

void Tracker::setFaceMinSize(int size) {
	mFaceMinSize = size;
}

bool Tracker::init() {
	if (!mFaceClassifier.load(mFaceXml)) {
		return false;
	}
	if (!mEyeClassifier.load(mEyeXml)) {
		return false;
	}

	return true;
}

void Tracker::process(Mat rgba , Mat gray) {

	cv::equalizeHist(gray , gray);

	std::vector<Rect> faces = detectFaces( rgba , gray);

	std::vector<Rect> eyes = detectEyes(rgba , gray, faces);

}

std::vector<Rect> Tracker::detectFaces(Mat rgba , Mat gray) {
	std::vector<Rect> faces;
	mFaceClassifier.detectMultiScale(gray, faces, 1.3, 2,
			0 | CV_HAAR_SCALE_IMAGE, Size(mFaceMinSize , mFaceMinSize));

	return faces;
}

std::vector<Rect> Tracker::detectEyes(Mat rgba , Mat gray, std::vector<Rect> faces) {

	std::vector<Rect> eyes;

	for (int i = 0; i < faces.size(); i++) {
		rectangle(rgba , faces[i] , Scalar(255 , 255 , 0) , 3 , 3);

		Mat roi = gray(faces[i]);
		Mat rgbaRoi = rgba(faces[i]);
		mEyeClassifier.detectMultiScale(roi, eyes, 1.1, 2,
				0 | CV_HAAR_SCALE_IMAGE, Size(mEyeMinSize, mEyeMinSize));

		for( int j = 0 ; j < eyes.size() ; j++ ){

			rectangle(rgbaRoi , eyes[j] , Scalar(200 , 200 , 200) , 4 , 4);
		}

	}
	return eyes;
}

