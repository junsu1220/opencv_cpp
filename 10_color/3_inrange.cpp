#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
// 두 개의 트랙바 위치를 저장할 정수형 변수 lower_hue, upper_hue를 전역변수로 선언합니다.
int lower_hue = 40, upper_hue = 80;
// main()함수와 트랙바 콜백함수 on_hue_change()함수에서 함께 사용할
// Mat 객체를 전역변수로 선언합니다.
Mat src, src_hsv, mask;

void on_hue_changed(int, void*);

int main(int argc, char* argv[])
{
	// candies를 src 변수(Mat)에 저장합니다.
	src = imread("candies.png", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}
	// src영상을 HSV 색공간으로 변환하여 src_hsv에 저장합니다.
	cvtColor(src, src_hsv, COLOR_BGR2HSV);

	imshow("src", src);

	namedWindow("mask");
	// 색상의 하한 값과 상한 값을 조절할 수 있는 두 개의 트랙바를 생성합니다.
	// 색상의 최대값을 179로 설정하고, 두 트랙바의 콜백함수를 on_hue_changed()로 합니다.
	createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed);
	createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed);
	// 프로그램 처음 실행시 정상적으로 출력되도록 트랙바콜백함수를 강제로 호출합니다.
	on_hue_changed(0, 0);

	waitKey();
	return 0;
}

void on_hue_changed(int, void*)
{
	// 사용자가 임의로 지정한 색상의 하한값과 상한값을 이용하여 lowerb, upperb
	// 객체를 생성합니다. 채도의 범위는 임의로 100부터 255로 설정하였습니다.
	// 명도의 영향은 무시하도록 범위를 0부터 255로 설정하였습니다.
	Scalar lowerb(lower_hue, 100, 0);
	Scalar upperb(upper_hue, 255, 255);
	// src_hsv 영상에서 HSV 색 성분 범위가 lowerb부터 upperb사이인 위치의
	// 픽셀만 흰색으로 설정한 mask 영상을 생성합니다.
	inRange(src_hsv, lowerb, upperb, mask);

	imshow("mask", mask);
}
