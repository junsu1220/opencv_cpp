#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
	// pepper영상을 3채널BGR컬러로 불러와 src에 저장합니다.
	Mat src = imread("pepper.bmp", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}
	// BGR 색 공간의 src 영상을 YCrCb 색공간으로 변경하여 src_ycrcb에 저장합니다.
	Mat src_ycrcb;
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);
	// src_ycrcb 영상의 채널을 분리하여 ycrcb_planes에 저장합니다.
	vector<Mat> ycrcb_planes;
	split(src_ycrcb, ycrcb_planes);
	// Y성분에 해당하는 ycrcb_planes[0]영상에만 히스토그램 평활화를 수행합니다.
	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]); // Y channel
	// dst를 선언하고 다시 세 영상을 합쳐서 dst영상을 생성합니다.
	Mat dst_ycrcb;
	merge(ycrcb_planes, dst_ycrcb);
	// dst영상의 색공간을 BGR 색공간으로 변환하여 dst에 저장합니다.
	Mat dst;
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	return 0;
}