#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void mask_setTo();
void mask_copyTo();
void time_inverse();
void useful_func();

int main(void)
{
	mask_setTo();
	mask_copyTo();
	time_inverse();
	useful_func();

	return 0;
}

void mask_setTo()
{
	// 레나영상을 src변수에 저장합니다.
	Mat src = imread("lenna.bmp", IMREAD_COLOR);
	// 마스크영상을 mask변수에 저장합니다.
	Mat mask = imread("mask_smile.bmp", IMREAD_GRAYSCALE);
	// 예외처리
	if (src.empty() || mask.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// mask영상에서 픽셀값이 0이 아닌 위치에서만 src영상 픽셀을 
	// 노란색으로 설정합니다.
	// 마스크 행렬의 원소가 0이 아닌 위치에서만 value값이 설정되어 노랑색으로 나오는 것입니다.
	src.setTo(Scalar(0, 255, 255), mask);

	imshow("src", src);
	imshow("mask", mask);

	waitKey();
	destroyAllWindows();
}

void mask_copyTo()
{
	// 비행기 영상을 src 변수에 저장합니다.
	Mat src = imread("airplane.bmp", IMREAD_COLOR);
	// 비행기 마스크 영상을 mask 변수에 저장합니다.
	Mat mask = imread("mask_plane.bmp", IMREAD_GRAYSCALE);
	// 들판 영상을 dst 변수에 저장합니다.
	Mat dst = imread("field.bmp", IMREAD_COLOR);
	// 예외처리
	if (src.empty() || mask.empty() || dst.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// mask 영상에서 흰색영역위치에서만 src영상 픽셀 값을 dst로 복사합니다.
	src.copyTo(dst, mask);

	imshow("src", src);
	imshow("dst", dst);
	imshow("mask", mask);

	waitKey();
	destroyAllWindows();
}

void time_inverse()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	// 예외처리
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());
	// TickMeter 클래스 객체 tm을 선언합니다.
	TickMeter tm;
	// 시간측정을 시작합니다.
	tm.start();

	// 시간측정할 내용으로 영상의 모든픽셀을 반전시킵니다.
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = 255 - src.at<uchar>(j, i);
		}
	}
	// 시간측정 종료
	tm.stop();
	// 측정시간을 콘솔 창에 출력합니다.
	cout << "Image inverse took " << tm.getTimeMilli() << "ms." << endl;
}

void useful_func()
{
	// 그레이스케일 레나 영상
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);
	// 예외처리
	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// sum은 각 채널의 합(행렬의 전체 원소합)을 Scalar자료형으로 반환합니다.
	// mean은 각 채널의 평균(행렬의 평균)을 Scalar자료형으로 반환합니다.
	// 첫번째 원소값을 참조하기위해 [0]을 추가로 붙여서 작성했습니다.
	cout << "Sum: " << (int)sum(img)[0] << endl;
	cout << "Mean: " << (int)mean(img)[0] << endl;
	// Sum: 32518590
	// Mean: 124

	// minMaxLoc()는 행렬의 최솟값, 최댓값, 최솟값과 최댓값의 좌표정보를 알아낼 수 있습니다.
	// 최솟값 최댓값을 받는변수는 double형으로
	double minVal, maxVal;
	// 최대최소위치를 받을 변수는 Point자료형으로 선언했습니다.
	Point minPos, maxPos;
	// 함수인자에는 변수의 주소를 넘겨주어야 하므로 &연산자를 함께 사용합니다.
	// 마스크연산을 지원하므로 행렬 일부 영역에서의 최소최대값, 위치를 구할 수 있습니다.
	minMaxLoc(img, &minVal, &maxVal, &minPos, &maxPos);

	cout << "minVal: " << minVal << " at " << minPos << endl;
	cout << "maxVal: " << maxVal << " at " << maxPos << endl;
	// minVal: 25 at [508, 71]
	// maxVal: 245 at [116, 273]


	// normalize()는 행렬의 norm값을 정규화하거나 
	// 또는 원소 값 범위를 특정 범위로 정규화할 때 사용합니다.
	// 예를들어 -1에서 1사이의 실수로 구성된 1*5행렬을 0부터 255사이의
	// 정수행렬로 변환하려면 
	Mat src = Mat_<float>({ 1, 5 }, { -1.f, -0.5f, 0.f, 0.5f, 1.f });

	Mat dst;
	// (입력행렬, 출력행렬, (노름정규화->목표노름값, 원소값범위정규화->최솟값)
	// 최댓값, 정규화타입(minmax 원소값크기조절 자주쓰임), 결과영상타입)
	normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);

	cout << "src: " << src << endl;
	cout << "dst: " << dst << endl;
	// src: [-1, -0.5, 0, 0.5, 1]
	// dst: [0, 64, 128, 191, 255]


	// 실수값의 반올림을 연산을 위해 cvRound()를 제공합니다.
	// value인자의 소수점 아래가 0.5보다 크면 올림
	// 0.5보다 작으면 내림 0.5이면 가까운 짝수로 반올림을 수행합니다.
	cout << "cvRound(2.5): " << cvRound(2.5) << endl;
	cout << "cvRound(2.51): " << cvRound(2.51) << endl;
	cout << "cvRound(3.4999): " << cvRound(3.4999) << endl;
	cout << "cvRound(3.5): " << cvRound(3.5) << endl;
	// cvRound(2.5): 2
	// cvRound(2.51): 3
	// cvRound(3.4999): 3
	// cvRound(3.5): 4
}