#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	// Calculate CrCb histogram from a reference image

	Mat ref, ref_ycrcb, mask;
	// 피부색 히스토그램 정보를 추출할 기준 영상 ref를 불러옵니다.
	ref = imread("ref.png", IMREAD_COLOR);
	// 기준 영상에서 피부색이 있는 위치를 흰색으로 표시한 마스크영상 mask를 불러옵니다.
	mask = imread("mask.bmp", IMREAD_GRAYSCALE);
	// 기준 영상을 YCrCb 색 공간으로 변환합니다.
	cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);

	// 기준 영상에서 피부색 영역의 CrCb 2차원 히스토그램을 계산하여 
	// hist에 저장합니다.
	Mat hist;
	int channels[] = { 1, 2 };
	int cr_bins = 128; int cb_bins = 128;
	int histSize[] = { cr_bins, cb_bins };
	float cr_range[] = { 0, 256 };
	float cb_range[] = { 0, 256 };
	const float* ranges[] = { cr_range, cb_range };

	calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);

	// Apply histogram backprojection to an input image
	// 입력 영상 kids를 불러와 YCrCb 색공간으로 변환합니다.
	Mat src, src_ycrcb;
	src = imread("kids.png", IMREAD_COLOR);
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);
	// 앞서 구한 히스토그램 hist를 이용하여 입력영상에서 히스토그램 역투영을 
	// 수행합니다. 역투영결과는 backproj에 저장됩니다.
	Mat backproj;
	calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);

	imshow("src", src);
	imshow("backproj", backproj);
	waitKey();

	return 0;
}
