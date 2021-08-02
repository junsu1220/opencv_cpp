#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void sobel_derivative();
void sobel_edge();
void canny_edge();

int main(void)
{
	sobel_derivative();
	sobel_edge();
	canny_edge();

	return 0;
}
// 중앙차분미분 구현
void sobel_derivative()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// 중앙차분 미분근사마스크 구현 부분
	Mat mx = Mat_<float>({ 1, 3 }, { -1 / 2.f, 0, 1 / 2.f });
	Mat my = Mat_<float>({ 3, 1 }, { -1 / 2.f, 0, 1 / 2.f });

	Mat dx, dy;
	filter2D(src, dx, -1, mx, Point(-1, -1), 128);
	filter2D(src, dy, -1, my, Point(-1, -1), 128);

	imshow("src", src);
	imshow("dx", dx);
	imshow("dy", dy);

	waitKey();
	destroyAllWindows();
}

void sobel_edge()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// x축,y축으로 1차 편미분을 구하여 dx,dy행렬에 저장합니다.
	// dx,dy행렬은 float 자료형을 사용합니다.
	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);

	Mat fmag, mag;
	// dx,dy의 그래디언트크기를 계산해서 fmag에 저장합니다.
	// dx,dy가 float이므로 fmag도 float자료형을 사용하는 행렬로 생성됩니다.
	magnitude(dx, dy, fmag);
	// fmag를 그레이스케일로 변환하여 mag에 저장합니다.
	fmag.convertTo(mag, CV_8UC1);
	// 에지 판별을 위한 그래디언트 크기 임계값을 150으로 설정하여 에지를 판별합니다.
	// 행렬 edge의 원소값은 mag 행렬원소값이 150보다 크면 255, 작으면 0으로 설정됩니다.
	Mat edge = mag > 150;

	imshow("src", src);
	imshow("mag", mag);
	imshow("edge", edge);

	waitKey();
	destroyAllWindows();
}

void canny_edge()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst1, dst2;
	// 낮은임계값을 50, 높은임계값을 100으로 설정하여 케니에지수행
	// 그 결과를 dst1에 저장합니다.
	Canny(src, dst1, 50, 100);
	// 낮은임계값을 50, 높은임계값을 150으로 설정하여 케니에지수행
	// 그 결과를 dst2에 저장합니다.
	Canny(src, dst2, 50, 150);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}