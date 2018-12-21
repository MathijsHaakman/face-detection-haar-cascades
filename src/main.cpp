#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;
void detectAndDisplay(Mat frame);
CascadeClassifier face_cascade;
int main(int argc, const char** argv)
{
	CommandLineParser parser(argc, argv,
		"{help h||}"
		"{face_cascade|../../../xml/cascade_face.xml|Path to face cascade.}"
		"{camera|0|Camera device number.}");
	parser.about("\nThis program demonstrates using the cv::CascadeClassifier class to detect objects (Face) in a video stream.\n"
		"You can use Haar or LBP features.\n\n");
	parser.printMessage();
	String face_cascade_name = parser.get<String>("face_cascade");
	//-- 1. Load the cascades
	if (!face_cascade.load(face_cascade_name))
	{
		cout << "--(!)Error loading face cascade\n";
		return -1;
	}
	int camera_device = parser.get<int>("camera");
	VideoCapture capture;
	//-- 2. Read the video stream
	capture.open(camera_device);
	if (!capture.isOpened())
	{
		cout << "--(!)Error opening video capture\n";
		return -1;
	}
	Mat frame;
	while (capture.read(frame))
	{
		if (frame.empty())
		{
			cout << "--(!) No captured frame -- Break!\n";
			break;
		}
		//-- 3. Apply the classifier to the frame
		detectAndDisplay(frame);
		if (waitKey(10) == 27)
		{
			break; // escape
		}
	}
	return 0;
}
void detectAndDisplay(Mat frame)
{
	Mat frame_gray;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- Detect faces
	std::vector<Rect> faces;
	face_cascade.detectMultiScale(frame_gray, faces);
	for (size_t i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
		ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
		Mat faceROI = frame_gray(faces[i]);
	}
	//-- Show what you got
	imshow("Capture - Face detection", frame);
}