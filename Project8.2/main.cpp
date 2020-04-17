#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main()
{
	Mat srcMat, dstMat, binMat;
	srcMat = imread("D:\\2.png", 0);
	dstMat = imread("D:\\2.png");

	Mat src1Mat = 255 - srcMat;
	threshold(src1Mat, binMat, 150, 255, THRESH_OTSU);

	Mat element = getStructuringElement(MORPH_RECT, Size(7, 7));
	morphologyEx(binMat, binMat, MORPH_CLOSE, element);
	vector<vector<Point>> contours;
	findContours(binMat, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i < contours.size(); i++)
	{

	
		drawContours(dstMat, contours, i, Scalar(0, 255, 255), 1, 8);

		RotatedRect rbox = minAreaRect(contours[i]);
		Point2f vtx[4];
		rbox.points(vtx);
		for (int j = 0; j < 4; ++j) {
			float Y = sqrt((vtx[0].y - vtx[1].y) * (vtx[0].y - vtx[1].y) + (vtx[0].x - vtx[1].x) * (vtx[0].x - vtx[1].x));
			float X = sqrt((vtx[1].y - vtx[2].y) * (vtx[1].y - vtx[2].y) + (vtx[1].x - vtx[2].x) * (vtx[1].x - vtx[2].x));

			float kuanchangbi[5];
			kuanchangbi[i] = Y / X;
			float mianji = X * Y;
			if (mianji < 6000 && mianji>2000)
			{
				cv::line(dstMat, vtx[j], vtx[j < 3 ? j + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);
			}

		}
	}
	imshow("src", srcMat);
	imshow("dst", dstMat);

	waitKey(0);
}