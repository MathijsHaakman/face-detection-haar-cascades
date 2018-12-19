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
		"{face_cascade|../../data/haarcascades/haarcascade_frontalface_alt.xml|Path to face cascade.}"
		"{image|../../../images/positive/IMG_7867.JPG|Image to detect face in.}");
	parser.about("\nThis program demonstrates using the cv::CascadeClassifier class to detect objects (Face) in an image.\n"
		"You can use Haar or LBP features.\n\n");
	parser.printMessage();
	// String face_cascade_name = parser.get<String>("face_cascade");
	String face_cascade_name = "D:\\Keut\\Documents\\Git\\face-detection-haar-cascades\\xml\\haarcascade_frontalface_alt.xml";
	// String image_path = parser.get<String>("image");
	String image_path = "D:\\Keut\\Documents\\Git\\face-detection-haar-cascades\\images\\guess\\IMG_20181219_222333.jpg";
	cout << face_cascade_name << "  test  " << image_path << endl;
	//-- 1. Load the cascades
	if (!face_cascade.load(face_cascade_name))
	{
		cout << "--(!)Error loading face cascade\n";
		return -1;
	};
	Mat img;
	img = imread(image_path, IMREAD_COLOR);
	if (img.empty())
		std::cout << "failed to open img.jpg" << std::endl;
	detectAndDisplay(img);
	waitKey(0);
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
	namedWindow("Capture - Face detection", WINDOW_NORMAL | WINDOW_KEEPRATIO);
	imshow("Capture - Face detection", frame);
}